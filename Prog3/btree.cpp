#include "btree.h"

//default constructor
BTree:: BTree()
{
    height=0; read=0; write=0;
}

//prints to screen at the beginning of the program
void BTree:: writeHeader (char * fileName)
{
    treeFile.open(fileName, ios::in |ios::out);
    treeFile.seekg(0, ios::beg);
    BTNode dummy;
    treeFile.read((char *) & dummy, sizeof(BTNode));
    rootAddr = dummy.child[0];
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
    
    if(!isLeaf(recAddr))
    {
        //recrusively loop through until you get to leaf
        for(int i=0; i<dummy.currSize; i++)
        {
            if(key<dummy.contents[i])
            {
                insert(key,dummy.child[i]);
            }
        }
        insert(key,dummy.child[dummy.currSize]);
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
        cout<<"Now inserting "<<key.getUPC()<<endl;

        //write back out to file
        treeFile.seekg(recAddr,ios::beg);
        treeFile.write((char *) & dummy, sizeof(BTNode));
        write++;
    }
    //node is full, must split
    else
    {
        splitNode(key, recAddr, -1, -1);
        cout<<"Now splitting "<<endl;
    }
}

void BTree:: reset (char * filename)
{
   treeFile.seekg(0);
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
    BTNode dummy = getNode(rootAddr);
    for(int i=0; i<=dummy.currSize; i++)
    {
        //checks to see if node is a leaf, if it is a leaf, recursively goes through
        //tree untill it gets to leaf, and prints all children
        if(dummy.child[i] != -1)
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
            return true;

        else if(key < t.contents[i].getUPC() && !isLeaf(t))
            return search(key, t, tAddr);
    }
    if(isLeaf(t))
        return false;
    else
        return search(key, t, tAddr);
}

/*	
keyType BTree:: retrieve (string key)
{

}
*/

//totals the amount of times gone out to disk
void BTree:: totalio() const
{
    cout<<"total read: "<<read<<endl;
    cout<<"total write: "<<write<<endl;
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

//private
int BTree:: findAddr (keyType key, BTNode t, int tAddr)
{
    for(int i=0; i<t.currSize; i++)
    {
        if(key == t.contents[i])
            return tAddr;

        else if(key < t.contents[i] && !isLeaf(t))
            return findAddr(key, getNode(t.child[i]), t.child[i]);
    }
    if(isLeaf(t))
        return tAddr;
    else
        return findAddr(key, getNode(t.child[t.currSize]), t.child[t.currSize]);

}

//private function 
//tAddr is adress of current position, findAddr is the address of the parent (what you want)
int BTree:: findpAddr(keyType key, BTNode t, int tAddr, int findAddr)
{
    for(int i=0; i<t.currSize; i++)
    {
        if(findAddr == t.child[i])
            return tAddr;

        else if(key < t.contents[i] && !isLeaf(t))
            findpAddr(key, t, tAddr, findAddr);
    }
    //checking rightmost child
    if(isLeaf(t))
        return -1;
    else if(findAddr == t.child[t.currSize])
        return tAddr;
    else
        return findpAddr(key, t, tAddr, findAddr);
}

//private
BTNode BTree:: getNode(int recAddr)
{
    treeFile.seekg(recAddr, ios::beg);
    BTNode dummy;
    treeFile.read((char *) & dummy, sizeof(BTNode));
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

//private
void BTree:: adjRoot (keyType rootElem, int oneAddr, int twoAddr)
{

}

//private function. When first called, you are at a leaf node  
void BTree:: splitNode (keyType& key,int recAddr, int leftAddr, int rightAddr)
{
    BTNode leftChild = getNode(recAddr);
    BTNode parent = getNode(findpAddr(key, root, rootAddr, recAddr));
    
    //Case 1: leaf is full, and parent is not full
    if(parent.currSize < 4)
    {
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
            for(i=leftChild.currSize-1; (i>=0 && key < leftChild.contents[i]); i--)
            {
                leftChild.contents[i+1] = leftChild.contents[i];
                leftChild.contents[i+2] = leftChild.contents[i+1];
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

        treeFile.seekp(recAddr, ios::beg);
        treeFile.write((char *) & leftChild, sizeof(BTNode));

        treeFile.seekp(0,ios::end);
        int rightAddress = treeFile.tellp();
        treeFile.write((char *) & rightChild, sizeof(BTNode));
        
        //promoting child in position 2 to parent
        placeNode(leftChild.contents[2], findpAddr(key, root, rootAddr, recAddr), recAddr, rightAddress);
    }
}

//promote median value to parent node
void BTree:: placeNode (keyType key,int pAddr,int leftAddr,int rightAddr)
{
    BTNode parent = getNode(pAddr);
    BTNode left = getNode(leftAddr);
    BTNode right = getNode(rightAddr);

    //case if root is full, need to create new node and update root
    if(pAddr == -1)
    {
        BTNode newRoot;
        newRoot.contents[0] = key;
        newRoot.child[0] = leftAddr;
        newRoot.child[1] = rightAddr;
        
        treeFile.seekg(0,ios::end);
        treeFile.write((char *) & parent, sizeof(BTNode));
        rootAddr = treeFile.tellp();
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
        parent.currSize++;

        //write back out to file
        treeFile.seekg(pAddr,ios::beg);
        treeFile.write((char *) & parent, sizeof(BTNode));
        write++;
    }
    else
    {
        splitNode(key, pAddr, leftAddr, rightAddr);
    }
}
