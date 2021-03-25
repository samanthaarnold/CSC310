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

    multiset<string> f1;
    multiset<string> f2;
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

    multiset<string>::iterator i;
    multiset<string>::iterator j;
    for(i=f2.begin(); i!=f2.end(); i++)
    {
        //cout<<*i<<endl;
        j=f1.find(*i);
        if(j != f1.end())
        {
            cout<<*i<<endl;
        }
        
    }
}    