#include <iostream>
#include <bitset>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>
#include "file.h"
#include <filesystem> 

using namespace std;
//namespace fs = std::filesystem;

void getFile();
bool direcCheck(string & file);
File getStats(string & file);

int main(int argc, char **argv)
{
    string file1 = argv[1];
    getStats(file1);
    /*
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

    //-cf 
    if(b.test(0))
    {
        
    }
    */
}

//checks if directory
bool direcCheck(string & file)
{
    struct stat buf;
    lstat (file.c_str(), &buf);
    bool d;
    S_ISDIR(buf.st_mode)? d=true : d=false;
    return d;
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
    return f;
}

void getFile(string & file)
{
    //for(auto p: recursive_directory_iterator(file))
      //  cout << p.path() << '\n';
}
