#include <iostream>
#include <string.h>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    char * s = new char[25];
    char * sp = s;
    string line = ""; int i,j;

    cout<<"enter a num: ";
    cin>>j;
    strcpy(s,"01234");

    for(int i=0; i<j; i++)
    {
        //converting digit into char verison of itself
        *s =('1'+i%10);
        //adding the char s at that position
        line += *s;
        s++;
    }

    cout<<"s = "<<s<<"\nsp = "<<sp<<"\nline = "<<line<<endl;

    string sa = "our_program 0.01"; char ch;
    cout<<ch<<endl;
    istringstream is(sa);
    is >> sa >> ch;
    cout<< sa <<endl;
    cout<<ch<<endl;

    return 0;

}