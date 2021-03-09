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

void cf(char **argv, string & tarfileName);
File getStats(string & file);
void tf(string & tarfileName);

int main(int argc, char **argv)
{
    if(argc==1)
    {
        cout<<"Failure to specify one of the four options supported by jtar"<<endl;
        return 1;
    }

    //set boolean flags
    bitset<4>b;
    string tarfileName;
    for(int i=1; i<argc; i++)
    {
        if(strcmp(argv[i], "-cf")==0)
        {
            b.set(0);
            tarfileName = argv[i+1];
        }
        else if(strcmp(argv[i], "-tf")==0)
        {
            b.set(1);
            tarfileName = argv[i+1];
            //cout<<"-tf"<<endl;
            //break;
        }
        else if(strcmp(argv[i], "-xf")==0)
        {
            b.set(2);
            tarfileName = argv[i+1];
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
        cout<<"Invalid format for jtar -cf"<<endl;
        return 1;
    }
    if(argc<3 && (b.test(1) || b.test(2)) )
    {
        cout<<"Invalid format for jtar"<< (b.test(2)? " -tf" : " -xf") <<endl;
        return 1;
    }


    //-cf 
    if(b.test(0))
    {
        cf(argv, tarfileName);
    }
    //-tf
    if(b.test(1))
    {
        tf(tarfileName);
    }

}

// getStats returns a file object, so determines the name of the file or 
// directory, the protection mode, the size, and the timestamp in the form
// YrMonthDayHrMin. Used the code from utility.cpp 
File getStats(string & file)
{
    struct stat buf;
    char name[81], pmode[5], size[7], stamp[16];
    lstat (file.c_str(), &buf);
    
    //name
    strcpy(name,file.c_str());
    
    //pmode
    string protection;
    protection += ((buf.st_mode & S_IRWXU) >> 6)+((buf.st_mode & S_IRWXG) >> 3)+(buf.st_mode & S_IRWXO);
    strcpy(pmode,protection.c_str());
    
    //size
    string fileSize = to_string(buf.st_size);
    strcpy(size,fileSize.c_str());
    
    //stamp
    strftime(stamp, 16, "%Y%m%d%H%M.%S", localtime(&buf.st_mtime));

    File f(name,pmode,size,stamp);
    
    //check if file is directory
    if(S_ISDIR(buf.st_mode))
    {
        f.flagAsDir();
    }
    return f;
}

//-cf option creates the binary tarfileName. Name of tarfileName is specified on command
// line. Gets stats on all files or directories that are being compressed and 
// stores them in a vector of file objects. From there, the number of files is 
// written out to the tarfileName along with the name of all the files or directories.
// If the file is a text file, then write out all the characters to the tarfileName. 
void cf(char **argv,string & tarfileName)
{
    vector<File> pathways;
    string file = argv[3];
        
    for(auto p: recursive_directory_iterator(file))
    {
        string name = p.path();
        pathways.push_back( getStats(name) );   
    }

    fstream tarfile (tarfileName.c_str(), ios::out | ios::binary);
    
    //numner of files
    int totalFiles = pathways.size();
    tarfile.write( (char *) & totalFiles, sizeof(int) );
    //cout<<totalFiles<<"size of "<<sizeof(int)<<endl;
    
    for(int i=0; i < pathways.size(); i++)
    {
        tarfile.write( (char *) & pathways[i], sizeof(pathways[i]) );
        //if not a directory, need to write out data to tarfileName
        if(!pathways[i].isADir())
        {
            fstream tempFile (pathways[i].getName().c_str(), ios::in);
            char * token = new char[ stoi(pathways[i].getSize()) ]; //creating an array of chars that is size of file
            tempFile.read(token, stoi(pathways[i].getSize()) );     //reading the entire file in at once
            tarfile.write(token, stoi(pathways[i].getSize()) );     //writing data out to binary tar file
            tempFile.close();
        }   
    }
    tarfile.close();
}

//-tf
// reads binary tarfileName and prints out the list of names 
void tf(string & tarfileName) 
{
    fstream tarfile (tarfileName.c_str(), ios::in | ios::binary);
    
    char * totalFiles = new char[sizeof(int)];
    tarfile.read(totalFiles, sizeof(int) );
    //cout<<"total files= "<<totalFiles<<endl;

    tarfile.close();
}


