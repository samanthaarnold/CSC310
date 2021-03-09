#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>
#include "file.h"
#include <filesystem> 
#include <cstdlib>

using namespace std;
using recursive_directory_iterator = filesystem::recursive_directory_iterator;  

void cf(char **argv, string & tarfile);
File getStats(string & file);

int main(int argc, char **argv)
{
    if(argc==1)
    {
        cout<<"Failure to specify one of the four options supported by jtar"<<endl;
        return 1;
    }

    //set boolean flags
    bitset<4>b;
    string tarfile;
    for(int i=1; i<argc; i++)
    {
        if(strcmp(argv[i], "-cf")==0)
        {
            b.set(0);
            tarfile = argv[i+1];
        }
        else if(strcmp(argv[i], "-tf")==0)
        {
            b.set(1);
            cout<<"-tf"<<endl;
            //break;
        }
        else if(strcmp(argv[i], "-xf")==0)
        {
            b.set(2);
            cout<<"-xf"<<endl;
        }
        else if(strcmp(argv[i], "--help")==0)
        {
            b.set(3); system("cat help");
        }
        else if(b.none())
        {
            cout<<"Invalid option on the command line"<<endl;
            return 1;
        } 
    }

    //check arguments
    if(b.test(0) && argc<4)
    {
        cout<<"Invalid format for -cf"<<endl;
        return 1;
    }
    if(argc<3 && (b.test(1) || b.test(2)) )
    {
        cout<<"Invalid format for"<< (b.test(2)? " -tf" : " -xf") <<endl;
        return 1;
    }

////////////////////////////////////////////////////////////////////////////////////////////
    //-cf 
    if(b.test(0))
    {
        cf(argv, tarfile);
    }
//////////////////////////////////////////////////////////////////////////////////////////// 
}

File getStats(string & file)
{
    struct stat buf;
    char name[81], pmode[5], size[7], stamp[16];
    lstat (file.c_str(), &buf);
    
    //name
    strcpy(name,file.c_str());
    //cout<<"name= "<<name;
    
    //pmode
    string protection;
    //cout << ", protection = " << ((buf.st_mode & S_IRWXU) >> 6) << ((buf.st_mode & S_IRWXG) >> 3) << (buf.st_mode & S_IRWXO)<<endl;
    protection += ((buf.st_mode & S_IRWXU) >> 6)+((buf.st_mode & S_IRWXG) >> 3)+(buf.st_mode & S_IRWXO);
    strcpy(pmode,protection.c_str());
    
    //size
    string fileSize = to_string(buf.st_size);
    strcpy(size,fileSize.c_str());
    //cout << ", size = " << buf.st_size;
    
    //stamp
    strftime(stamp, 16, "%Y%m%d%H%M.%S", localtime(&buf.st_mtime));
    //cout << ", timestamp = " << stamp << endl;

    File f(name,pmode,size,stamp);
    
    //check if file is directory
    if(S_ISDIR(buf.st_mode))
    {
        f.flagAsDir();
    }
    return f;
}

void cf(char **argv,string & tarfile)
{
    vector<File> pathways;
    string file = argv[2];
        
    for(auto p: recursive_directory_iterator(file))
    {
        string name = p.path();
        pathways.push_back( getStats(name) );   
        //cout << p.path() << '\n';
    }

    fstream tarFile (tarfile, ios::in |ios::binary);

    //numner of files
    tarFile << pathways.size();
    //cout<<pathways.size()<<endl;
    
    for(int i=0; i < pathways.size(); i++)
    {
        tarFile.write( (char *) & pathways[i], sizeof(pathways[i]) );
        //if not a directory, need to write out data
        if(!pathways[i].isADir())
        {
            fstream tempFile (pathways[i].getName().c_str(), ios::in);
            char * token = new char[ stoi(pathways[i].getSize()) ]; //creating an array of chars that is size of file
            tempFile.read(token, stoi(pathways[i].getSize()) );     //reading the entire file in at once
            tarFile.write(token, stoi(pathways[i].getSize()) );     //writing data out to binary tar file
            tempFile.close();
        }   
    }
   
    tarFile.close();
}


