#include<iostream>
#include<string>
#include<fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
    if(argc < 3 || argc > 6)
    {
        cout<<"Please enter the correct number of arguments"<<endl;
        return 1;
    }

    bool c,iv = false;
    int iline=0;
    for(int i=1; i<argc -1; i++)
    {
        if(strcmp(argv[i], "-c")==0)
        {
            c=true;
            break;
        }
        else if(strcmp(argv[i], "-i")==0)
        {
            iline = atoi(argv[i+1]);
            iv=true;
            break;
        }
        else
        {
            cout<<"Please enter correct option"<<endl;
        }
        
    }

    int byte = 0;
    char ch1,ch2;
    int line = 1;

    //file1
    fstream inFile1(argv[argc-2], ios::in);
    //file2
    fstream inFile2(argv[argc-1], ios::in);
    
    //positions read head to 0 if no -i, and to correct position if -i
    if(iv)
        inFile1.seekg(iline,ios::beg); inFile2.seekg(iline,ios::beg);
    
    //check to make sure beginning of file is not an empty file
    /*
    if(inFile1.good() && byte==0)
    {   
        cout<<1<<endl;
        cout<<"cmp: EOF on "<<argv[argc-2]<<endl; 
    }
    if(inFile2.good() && byte==0)
    {
        cout<<2<<endl;
        cout<<"cmp: EOF on "<<argv[argc-1]<<endl;
    }   
    */

    while(inFile1.get(ch1) && inFile2.get(ch2))
    {
        byte++;
        //cout<<"ch1: "<<ch1<<"\t chr2: "<<ch2<<endl;
        if(ch1=='\n')
            line++;
   
        if(ch1!=ch2)
        {
            if(c)
            {
                cout<<"test"<<endl;
            } 
            else
            {
                cout<<argv[argc-2]<<" "<<argv[argc-1]<<" differ: byte "<<byte<<", line "<<line<<endl;
            }
            return 1;
        }
        
    }
    
    /*
    //reached end of inFile2 before inFile1
    if(inFile1.good() && !inFile2.good())
    {
        cout<<3<<endl;
        cout<<"cmp: EOF on "<<argv[argc-1]<<endl;
    }
    //reached end of inFile1 before inFile2
    if(!inFile1.good() && inFile2.good())
    {
        cout<<4<<endl;
        cout<<"cmp: EOF on "<<argv[argc-2]<<endl;
    }
    */


}