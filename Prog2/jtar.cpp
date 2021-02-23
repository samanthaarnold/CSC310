#include <iostream>
#include <bitset>
#include "file.h"

using namespace std;

int main(int argc, char **argv)
{
    if(argc==1)
    {
        cout<<"Failure to specify one of the four options supported by jtar"<<endl;
        return 1;
    }

    //set boolean flags
    bitset<4>b;
    for(int i=1; i<argc; i++)
    {
        if(strcmp(argv[i], "-cf")==0)
        {
            b.set(0);
            string tarfile= argv[i+1];
            cout<<"-cf"<<endl;
            //break;
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
            break;
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

}
