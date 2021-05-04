#include <fstream>
#include <iostream>
#include "btree.h"
#include "album.h"

using namespace std;

int main(int argc, char* argv[]) 
{
    BTree b;
    Album a;

    b.reset(argv[2]);

    //cout << b.root.currSize << endl;

    fstream temp(argv[1],ios::in);

    while( temp >> a )
    {
        
        cout<<a;
        cout<<endl;
        b.insert(a);
        
    }
    cout<<endl;
    b.printTree();

    temp.close();
    b.close();
}