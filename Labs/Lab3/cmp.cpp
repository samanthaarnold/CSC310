#include<iostream>
#include<string>
#include<fstream>
#include <cstring>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>

using namespace std;

int main(int argc, char **argv)
{
    if(argc < 3 || argc > 6) {
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
            cout<<"Please enter correct option"<<endl;
    }

    fstream inFile1(argv[argc-2], ios::in);
    fstream inFile2(argv[argc-1], ios::in);
    
    //Check if input is directory, code from Dr. Digh
    struct stat buf;
    for (int i = argc-2;  i < argc;  i++)
    {
        lstat (argv[i], &buf);
        if (S_ISREG(buf.st_mode)) 
        {
            //check to make sure beginning of file is not an empty file
            if(inFile1.peek() == EOF) 
            {   
                cout<<"cmp: "<<argv[argc-1]<<" is empty"<<endl;
                return 1; 
            }
            if(inFile2.peek() == EOF) 
            {
                cout<<"cmp: "<<argv[argc-2]<<" is empty"<<endl;
                return 1;
            }   
        }
        else if (S_ISDIR(buf.st_mode))
            cout << argv[i] << "is a directory "<<endl;
    }
    
    int byte = 0; char ch1,ch2; int line = 1;

    //positions read head to 0 if no -i, and to correct position if -i
    if(iv)
        inFile1.seekg(iline,ios::beg); inFile2.seekg(iline,ios::beg);
    
   
    while(inFile1.get(ch1) && inFile2.get(ch2)) {
        byte++;
        if(ch1=='\n')
            line++;
        if(ch1!=ch2) 
        {
            if(c) 
            {
                printf("%s %s differ: char %d, line %i is %o %c %o %c ", argv[argc-2], argv[argc-1], byte, line, ch1, ch1, ch2, ch2);
                cout<<endl;
            } 
            else 
            {
                cout<<argv[argc-2]<<" "<<argv[argc-1]<<" differ: byte "<<byte<<", line "<<line<<endl;
            }
            return 1;
        } 
    }

    //reached end of inFile2 before inFile1
    if(inFile1.peek() != EOF && inFile2.peek() == EOF )
        cout<<"cmp: EOF on "<<argv[argc-1]<<endl;

    //reached end of inFile1 before inFile2
    if(inFile1.peek() == EOF && inFile2.peek() != EOF )
        cout<<"cmp: EOF on "<<argv[argc-2]<<endl;
    
    return 0;
}