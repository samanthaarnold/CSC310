#include<iostream>
#include<string>
#include<fstream>
#include <cstring>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>

using namespace std;

bool validName(string & name);

int main(int argc, char ** argv) {
    string Name = "file5";
    
    cout<<boolalpha<<validName(Name)<<endl;

}

bool validName(string & name) {
    struct stat buf;
    lstat (name.c_str(), &buf);
        if (S_ISREG(buf.st_mode)) 
        {
            return true;
        }
        else if (S_ISDIR(buf.st_mode)) 
        {
            return true;
        }
        else 
        {
            return false;
        }
}
        


