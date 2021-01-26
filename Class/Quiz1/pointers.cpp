#include <iostream>
#include <string.h>
#include <string>

using namespace std;

int main()
{
    char * s = new char[25];
    char * sp = s;
    string line = ""; int i,j;

    cout<<"enter a num: ";
    cin>>j;
    strcpy(s,"0123456789");

    for(int i=0; i<j; i++)
    {
        //converting digit into char verison of itself
        *s =('0'+i%10);
        //adding the char s at that position
        line += *s;
        s++;
    }

    cout<<"s = "<<s<<"\nsp = "<<sp<<"\nline = "<<line<<endl;
    return 0;

}