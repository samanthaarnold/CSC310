#include <fstream>
#include <iostream>
#include <cctype>

using namespace std;

int main(int argc, char* argv[])
{
    fstream inFile("fileSum", ios::in);
    
    /* filebuf fb;
    if (fb.open ("fileSum.txt", ios::in) )
    {
        istream is(&fb);
        
        while (is)
        {
            cout << is <<endl;;
        }
        fb.close();
    }
    cout<<"test"<<endl;
    */

    int sum =0;
    char x;
    
    int c = inFile.peek();
    cout<<"peek: "<<c<<endl;
    
    while(inFile >> x)
    {
        
        if(isdigit(c))
        {
            sum += x;
            cout<<"current sum "<<sum<<endl;
        }

        if(c == ',' || c == ' ')
        {
            inFile.ignore();
        }

        if(c == ';')
        {
            return -1;
        }
    }
    
   
    cout<<sum<<endl;

    return 0;
}