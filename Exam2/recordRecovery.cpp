#include<iostream>
#include<fstream>
#include<string>
#include<string.h> 
#include <sstream>
#include <cstdlib>
#include <utility>

using namespace std;

int main(int argc, char **argv)
{
    fstream indexFile("indexFile", ios::in|ios::out);
    fstream stackFile("stackFile", ios::in|ios::out);
    

    int totalAvil = 0;
    stackFile >> totalAvil;
    
    //skip to last record  General Formula: 5+(10*(totalAvil-1))
    stackFile.seekg(5+(10*(totalAvil-1)));

    int offset=0; 

    stackFile>>offset; 
    
    int iOffset=0; 
   
    indexFile.seekg(9);
    //seekg to position offset location, change minus to plus
    while(indexFile >> iOffset) {
        if(iOffset == offset) {
            //cout<<"correct location"<<endl;
            
            indexFile.seekg(7,ios::cur);
            indexFile << '+'; 
        }
        //cout<<iOffset<<endl;
        indexFile.seekg(13, ios::cur);
    }

    //update avil file
    stackFile.seekg(0,ios::beg);
    stackFile << (totalAvil-1);
 
    indexFile.close();
    stackFile.close();
}