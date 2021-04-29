#include "btree.h"

//default constructor
BTree:: BTree()
{

}

//prints to screen at the beginning of the program
void BTree:: writeHeader (char * fileName)
{

}

//public function, calls the private function insert
void BTree:: insert (keyType key)
{

}
//private function, inserts keyType 
void BTree:: insert (keyType key, int recAddr, int oneAddr, int twoAddr)
{

}

void BTree:: reset (char * filename)
{

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
void BTree:: inorder (int rootAddr)
{
    /*
    if(rootAddr != -1)
    {
        BTNode dummy = getNode(rootAddr);
        printNode(rootAddr);
        for(int i=0; i<=dummy.currSize; i++)
            printTree(dummy.child[i]);
    }
    */
}

//public function, calls private reverse function
void BTree:: reverse()
{

}
//private function,
void BTree:: reverse (int rootAddr)
{

}
	
int BTree:: getHeight()
{
    return height;
}

bool BTree:: search (string key)
{

}
//private
bool BTree:: search (string key, BTNode t, int tAddr)
{

}
	
keyType BTree:: retrieve (string key)
{

}

//totals the amount of times gone out to disk
void BTree:: totalio() const
{

}

int BTree:: countLeaves()
{
    
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

}

//private 
int BTree:: findpAddr(keyType key, BTNode t, int tAddr)
{
    
}

//private
BTNode BTree:: getNode(int recAddr)
{
    
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

}

//private
bool BTree:: isLeaf(BTNode t)
{

}

//private
void BTree:: adjRoot (keyType rootElem, int oneAddr, int twoAddr)
{

}

//private      
void BTree:: splitNode (keyType& key,int recAddr,int& oneAddr,int& twoAddr)
{

}