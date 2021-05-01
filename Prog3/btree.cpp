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
}

//public function, calls the private function insert
void BTree:: insert (keyType key)
{
    //insert(key, rootAddr, oneAddr, twoAddr);
}
//private function, inserts keyType 
// key is value inseting, recAddr is addess of current node 
void BTree:: insert (keyType key, int recAddr, int oneAddr, int twoAddr)
{
    BTNode dummy = getNode(recAddr);
    
    if(!isLeaf(recAddr))
    {
        //recrusively loop through until you get to leaf
        for(int i=0; i<dummy.currSize; i++)
        {
            if(key<dummy.contents[i])
            {
                insert(key,dummy.child[i], oneAddr, twoAddr);
            }
        }
        insert(key,dummy.child[dummy.currSize], oneAddr, twoAddr);
    }
    //node is a leaf, and node is not full
    else if(isLeaf(recAddr) && dummy.currSize < 4 )
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
    }
    //node is full, must split
    else
    {
        splitNode(key, recAddr, oneAddr, twoAddr);
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
    search(key, root, rootAddr);
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
	
keyType BTree:: retrieve (string key)
{

}

//totals the amount of times gone out to disk
void BTree:: totalio() const
{
    cout<<"total read: "<<read<<endl;
    cout<<"total write: "<<write<<endl;
}

int BTree:: countLeaves()
{
    countLeaves(rootAddr);
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
            findAddr(key, t, tAddr);
    }
    if(isLeaf(t))
        return tAddr;
    else
        return findAddr(key, t, tAddr);

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
void BTree:: placeNode (keyType k,int recAddr,int oneAddr,int twoAddr)
{

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
void BTree:: splitNode (keyType& key,int recAddr,int& oneAddr,int& twoAddr)
{

}