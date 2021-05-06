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

    fstream temp(argv[1],ios::in);

    while( temp >> a )
    {
        cout<<"Now inseting "<<a<<endl;
        b.insert(a);
    }
    
    cout<<endl;
    b.printTree();
    // cout << "***********************************************************" << endl;
    //b.inorder();

    temp.close();
    b.close();
}