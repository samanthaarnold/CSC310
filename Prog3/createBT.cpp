#include <fstream>
#include <iostream>
#include "btree.h"

using namespace std;

int main(int argc, char* argv[]) 
{
    BTree b;
    Album a;
    
    b.writeHeader(argv[1]);
    
    fstream temp(argv[1],ios::in);
    
    while( temp >> a )
    {
        b.insert(a);
    }

    temp.close();
    b.close();
}