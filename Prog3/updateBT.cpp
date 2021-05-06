#include "btree.h"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    
    fstream temp(argv[2],ios::in);
   
    BTree b;
    b.writeHeader(argv[1]);

    string c; string key;
    while( getline(temp,c) )
    {
        //search through b-tree and check UPC 
        if(c[0] == 'S')
        {
            getline(temp, key);
            if( b.search(key))
            {
                //cout<<"true"<<endl;
                cout<<"\t";
                Album a =  b.retrieve(key);
                cout<<a<<endl;
            }
            else
            {
                cout<<"\""<<key<<"\" not found"<<endl;
            }

        }
        //insert new record to b-tree
        else
        {
            Album a;
            temp >> a; 
            b.insert(a);
            cout<<"Now inserting "<<a<<endl;
        }
    }
    cout<<endl;
    b.totalio();

    b.close();
    temp.close();
    return 0;
}