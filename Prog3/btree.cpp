#include "btree.h"

//default constructor
BTree:: BTree()
{
    height=0; read=0; write=0;
}

//prints to screen at the beginning of the program
void BTree:: writeHeader (char * fileName)
{
    treeFile.open(fileName, ios::in |ios::out | ios::binary);
    treeFile.seekg(0, ios::beg);
    BTNode dummy;
    treeFile.read((char *) & dummy, sizeof(BTNode));
    cout << dummy.child[0] << endl;
    rootAddr = dummy.child[0];
    root = getNode(rootAddr);
    read++;
}

//public function, calls the private function insert
void BTree:: insert (keyType key)
{
    insert(key, rootAddr);
}
//private function, inserts keyType 
// key is value inseting, recAddr is addess of current node 
void BTree:: insert (keyType key, int recAddr)
{
    BTNode dummy = getNode(recAddr);
    
    //check if you are at a leaf
    if(!isLeaf(recAddr))
    {
        //recrusively loop through until you get to leaf
        for(int j=0; j<dummy.currSize; j++)
        {
            if(key<dummy.contents[j]) {
                insert(key,dummy.child[j]);
                return;
            }
        }
        insert(key,dummy.child[dummy.currSize]);
        return;
    }
    //node is a leaf, and node is not full
    else if( isLeaf(recAddr) && dummy.currSize < 4 )
    {
        int i;
        //finding correcting location to insert key to node
        for(i=dummy.currSize-1; (i>=0 && key < dummy.contents[i]); i--)
        {
            dummy.contents[i+1] = dummy.contents[i];
        }
        dummy.contents[i+1] = key;
        dummy.currSize++;

        //updating leaf in index file
        treeFile.seekg(recAddr,ios::beg);
        treeFile.write((char *) & dummy, sizeof(BTNode));
        write++;

        if(recAddr == rootAddr)
            root = dummy;
    }
    //node is full, must split
    else
    {
        cout << "Now spliting" << endl; 
        splitNode(key, recAddr, -1, -1); 
    }
}

//makes new b-tree
//opens file, makes dummy node 
void BTree:: reset (char * filename)
{
    //ios::trunc clears file every time so don't have a huge file
    treeFile.open(filename, ios::trunc | ios::in | ios::out | ios::binary);
    //setting first node (that contains no data) with the root address
    treeFile.seekg(0, ios::beg);
    BTNode dummy;
    dummy.child[0] = sizeof(BTNode);
    rootAddr = dummy.child[0];

    //setting children of root to -1
    root.currSize = 0;
    for(int i=0; i<ORDER; i++)
        root.child[i]=-1;

    //updating index file at first node and root node
    treeFile.write((char *) & dummy, sizeof(BTNode));
    write++;
    treeFile.write((char *) & root, sizeof(BTNode));
    write++;
}

//closes the fstream treeFile
void BTree:: close()
{
    treeFile.close();
}

//public function, calls private printTree
void BTree:: printTree()
{
    cout<<"-------- B-tree of height "<<height<<" --------"<<endl;
    printTree(rootAddr);
}
//private function, prints tree in preorder traversal (root, left, right)
void BTree:: printTree (int rootAddr)
{
    if(rootAddr != -1)
    {
        BTNode dummy = getNode(rootAddr);
        printNode(rootAddr);
        for(int i=0; i<=dummy.currSize; i++)
            printTree(dummy.child[i]);
    }
}

//public function, calls private print inorder
void BTree:: inorder()
{
    inorder(rootAddr);
}
//private function, prints the tree in inorder traversal (left, root, right)
//prints in accending order
void BTree:: inorder (int rootAddr)
{
    if(rootAddr == -1)
        return;

    BTNode dummy = getNode(rootAddr);
    for(int i=0; i<dummy.currSize; i++)
    {
        //recursively goes through tree untill it gets to leaf, and prints all children
        inorder(dummy.child[i]);
        cout<<dummy.contents[i]<<endl;
    }
    inorder(dummy.child[dummy.currSize]);
}

//public function, calls private reverse function
void BTree:: reverse()
{
    reverse(rootAddr);
}
//private function, prints tree in reverse order
//prints in decending order
void BTree:: reverse (int rootAddr)
{
    BTNode dummy = getNode(rootAddr);
    //recursively goes to link fartherest to left, and prints children starting at the back
    reverse(dummy.child[dummy.currSize]);
    //int = dummy.currSize-1 because you have one more link than children
    for(int i=dummy.currSize-1; i>=0; i--)
    {
        cout<<dummy.contents[i]<<endl;
        if(dummy.child[i] != -1)
            reverse(dummy.child[i]);
    }
}
	
int BTree:: getHeight()
{
    return height;
}


keyType BTree:: retrieve (string key)
{
    return retrieve (key, root, rootAddr);
}

keyType BTree:: retrieve (string key, BTNode t, int tAddr)
{
    for(int i=0; i<t.currSize; i++)
    {
        if(key == t.contents[i].getUPC())
        {
            return t.contents[i];
        }
    }
    for(int i=0; i<t.currSize; i++) 
    {
        if(key < t.contents[i].getUPC() && !isLeaf(t))
        {
            return retrieve(key, getNode(t.child[i]), t.child[i]);
        }
    }
    if( isLeaf(t) )
    {
        return keyType();
    }
    else
    {
        return retrieve(key, getNode(t.child[t.currSize]), t.child[t.currSize]);
    }
}

bool BTree:: search (string key)
{
    return search(key, root, rootAddr);
}
//private function. Loop through nodes, compare content to key and return true 
//if found. if key is smaller, go to child. If child is leaf, return -1
bool BTree:: search (string key, BTNode t, int tAddr)
{
    for(int i=0; i<t.currSize; i++)
    {
        if(key == t.contents[i].getUPC())
        {
            return true;
        }
    }
    for(int i=0; i<t.currSize; i++) 
    {
        if(key < t.contents[i].getUPC() && !isLeaf(t))
        {
            return search(key, getNode(t.child[i]), t.child[i]);
        }
    }
    if( isLeaf(t) )
    {
        return false;
    }
    else
    {
        return search(key, getNode(t.child[t.currSize]), t.child[t.currSize]);
    }
}

//totals the amount of times gone out to disk
void BTree:: totalio() const
{
    cout<<"\tTotal Reads: "<<read<<endl;
    cout<<"\tTotal writes: "<<write<<endl;
}

int BTree:: countLeaves()
{
    return countLeaves(rootAddr);
}
//private function, counts the number of leaves in every node. Uses recursions, assume
// -1 represents a null leaf
int BTree:: countLeaves(int recAddr)
{
    if(recAddr == -1)
        return 0;
    int numLeaves;
    if(recAddr != -1)
    {
        BTNode dummy = getNode(recAddr);
        for(int i=0; i<=dummy.currSize; i++)
            numLeaves+= countLeaves(dummy.child[i]);
    }
    return numLeaves;
}

//private function 
//tAddr is adress of current position, findAddr is the address of the parent (what you want)
int BTree:: findpAddr(keyType key, BTNode t, int tAddr, int findAddr)
{ 
    if(tAddr != -1) 
    {
        if(findAddr == rootAddr)
            return -1;
            
        for(int i=0; i<=t.currSize; i++) 
        {
            if(findAddr == t.child[i]) 
                return tAddr;
        }
        for(int i=0; i<t.currSize; i++) 
        {
            if(key < t.contents[i]) 
            {
                if(t.child[i] != -1) 
                    return findpAddr(key, getNode(t.child[i]), t.child[i], findAddr);
                else
                    return -1;
            }
        }
        //checking rightmost child
        if(isLeaf(t))
            return -1;
        else
            return findpAddr(key, getNode(t.child[t.currSize]), t.child[t.currSize], findAddr); 
    
    }
    return -1;
}

//private
BTNode BTree:: getNode(int recAddr)
{
    treeFile.seekg(recAddr, ios::beg);
    BTNode dummy;
    treeFile.read((char *) & dummy, sizeof(BTNode));
    read++;
    return dummy;
}

//private function, used to print the UPC, Artist, and Title that is in a node
void BTree:: printNode(int recAddr)
{
    treeFile.seekg(recAddr,ios::beg);
    BTNode dummy;
    treeFile.read((char*)& dummy, sizeof(BTNode));
    read++;
    cout<<" *** node of size "<<dummy.currSize<<" *** "<<endl;
    for (int i = 0; i < dummy.currSize; i++)
        cout<<dummy.contents[i]<<endl;
}

//private
bool BTree:: isLeaf (int recAddr)
{
    BTNode dummy = getNode(recAddr);
    return isLeaf(dummy);
}

//private
bool BTree:: isLeaf(BTNode t)
{
    if(t.child[0] == -1)
        return true;
 
    return false;
}

//private function. When first called, you are at a leaf node  
void BTree:: splitNode (keyType& key,int recAddr, int leftAddr, int rightAddr)
{
    BTNode leftChild = getNode(recAddr);
    BTNode parent = getNode(findpAddr(key, root, rootAddr, recAddr));

    if(key < leftChild.contents[3])
    {
        keyType temp = leftChild.contents[3];
        leftChild.contents[3] = key;
        key = temp;
        int tempAddr = leftChild.child[4];
        leftChild.child[4] = rightAddr;
        rightAddr = tempAddr;
       
        int i;
        //finding correcting location to insert key to node
        for(i=leftChild.currSize-1; (i>0 && leftChild.contents[i]<leftChild.contents[i-1]); i--)
        {
            temp = leftChild.contents[i];
            leftChild.contents[i] = leftChild.contents[i-1];
            leftChild.contents[i-1] = temp;

            tempAddr = leftChild.child[i+1];
            leftChild.child[i+1] = leftChild.child[i];
            leftChild.child[i] = tempAddr;
        }            
    }
        //splitting leftchild contents
        leftChild.currSize = 2;

        //adding content to right child, and updating the children 
        BTNode rightChild;
        rightChild.currSize=2;
        rightChild.contents[0] = leftChild.contents[3];
        rightChild.contents[1] = key;

        rightChild.child[0] = leftChild.child[3];
        rightChild.child[1] = leftChild.child[4];
        rightChild.child[2] = rightAddr;
        rightChild.child[3] = -1;
        rightChild.child[4] = -1;

        key=leftChild.contents[2];

        treeFile.clear();
        treeFile.seekp(recAddr, ios::beg);
        treeFile.write((char *) & leftChild, sizeof(BTNode));
        write++;

        treeFile.clear();
        treeFile.seekp(0,ios::end);
        int rightAddress = treeFile.tellp();
        treeFile.write((char *) & rightChild, sizeof(BTNode));
        write++;
    
        //promoting child in position 2 to parent
        placeNode(key, findpAddr(key, root, rootAddr, recAddr), recAddr, rightAddress);
    
}

//promote median value to parent node
void BTree:: placeNode (keyType key,int pAddr,int leftAddr,int rightAddr)
{
    BTNode parent = getNode(pAddr);
    BTNode left = getNode(leftAddr);
    BTNode right = getNode(rightAddr);
    
    //adjusting root
    if(pAddr == -1)
    {
        cout << "Now adjusting root" << endl;
        height++; 
        
        //promoting key to new node
        BTNode newRoot;
        newRoot.contents[0] = key;
        newRoot.currSize = 1;
        //setting left and right links as its children
        newRoot.child[0] = leftAddr;
        newRoot.child[1] = rightAddr;
        newRoot.child[2] = -1;
        newRoot.child[3] = -1;
        newRoot.child[4] = -1;

        //setting temparay root to BTNode root
        root = newRoot;
        root.currSize = 1;
        //writing new root node at the end of index file
        treeFile.clear();
        treeFile.seekg(0,ios::end);
        rootAddr = treeFile.tellp();
        treeFile.write((char *) & newRoot, sizeof(BTNode));
        write++;

        //updating child[0] at beginging of file with new root address
        treeFile.clear();
        treeFile.seekg(0, ios::beg);
        BTNode dummy;
        dummy.child[0] = rootAddr;
        treeFile.write((char *) & dummy, sizeof(BTNode));
        write++;
    }
    //parent node is not full
    else if(parent.currSize < 4)
    {
        int i;
        //finding correcting location to insert key to node and adjusting children
        for(i=parent.currSize-1; (i>=0 && key < parent.contents[i]); i--)
        {
            parent.contents[i+1] = parent.contents[i];
            parent.child[i+2] = parent.child[i+1];
        }
        parent.contents[i+1] = key;
        parent.child[i+2] = rightAddr;
        //updating size
        parent.currSize++;

        //updating index file with key
        treeFile.seekg(pAddr,ios::beg);
        treeFile.write((char *) & parent, sizeof(BTNode));
        write++;

        //special case for if we are updating the root
        if(pAddr == rootAddr)
        {
            root = parent;
        }      
    }
    //if parent node is full, split again 
    else
    {
        splitNode(key, pAddr, leftAddr, rightAddr);
    }
}
