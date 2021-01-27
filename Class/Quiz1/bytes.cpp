#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{

    fstream inout("library.dat", ios::in | ios::out);

    char a[10];
    int i=0;
    for(int j=700; j<=703; j++)
    {
        inout.seekg(j);
        inout.get(a[i]);
        i++;
    }
    cout<<a[0]<<" "<<a[3]<<endl;
    inout.seekp(701);
    if(a[0]<a[3])
    {
        inout << a[0] << a[3];
        cout<<"test"<<endl;
    }
    else
    {
        inout << a[3] << a[0];
    }
    

}