#include <iostream>
#include <bitset>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>
#include "file.h"

using namespace std;

void cf();
bool direcCheck(string & file);
string pmode(string & file);
int fileSize(string & file);
string timeStamp(string & file);


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

    //-cf 
    if(b.test(0))
    {
        //system("mkdir "+ tarfile);
        string file;
        for(int i=3; i<argc; i++)
        {
            file = argv[i];
            if( !direcCheck(file) )
            {
                
            }
            else
            {
                //cout<<"directory"<<endl;
                //f.flagAsDir();
            }
        }
    }
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

string pmode(string & file)
{
    string protection;
    struct stat buf;
    lstat (file.c_str(), &buf);
    cout << ", protection = " << ((buf.st_mode & S_IRWXU) >> 6) << ((buf.st_mode & S_IRWXG) >> 3) << (buf.st_mode & S_IRWXO)<<endl;
    protection += ((buf.st_mode & S_IRWXU) >> 6);
    return protection;
}

int fileSize(string & file)
{
    struct stat buf;
    lstat (file.c_str(), &buf);
    cout << ", size = " << buf.st_size;
    return buf.st_size;
}

string timeStamp(string & file) 
{
    struct stat buf;
    lstat (file.c_str(), &buf);

    char stamp[16];
    strftime(stamp, 16, "%Y%m%d%H%M.%S", localtime(&buf.st_ctime));
    
    cout << ", timestamp = " << stamp << endl;
    return stamp;
    /*
    timebuf.actime = buf.st_atime;
    timebuf.modtime = buf.st_mtime;

    utime (file.c_str(), &timebuf);
    */
}

void cf()
{

}
