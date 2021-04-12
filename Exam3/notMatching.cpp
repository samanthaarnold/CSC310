#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <set>

using namespace std;

int main(int argc, char **argv)
{
    fstream file1(argv[1], ios::in);
    fstream file2(argv[2], ios::in);

    set<string> f1;
    set<string> f2;
    string name1,name2;
    while(file1>>name1)
    {
        f1.insert(name1);
        //cout<<name1<<endl;
    }
    while(file2>>name1)
    {
        f2.insert(name1);
        //cout<<name2<<endl;
    }

    set<string>::iterator i = f2.begin();
    set<string>::iterator j = f1.begin();
    
    while(i != f2.end())
    {
        //reach end of file1, but not done with file2
        if(j==f1.end())
        {
            cout<<*i<<endl;
            i++;
        }
        //means two strings are the same
        else if(*i == *j)
        {
            //cout<<"enters"<<endl;
            i++;
            j++;
        }
        //name on file2 comes before name file1
        else if(*i<*j) {
            cout<<*i<<endl;
            i++;
        }
        else{
            cout<<*j<<endl;
            j++;
        }
    }
}    