#include<iostream>
#include<string>
#include <sstream>
#include <cstdlib>
#include <utility>

using namespace std;

string compress(string & input);
string uncompress(string & input);

int main(int argc, char **argv)
{
    string myInput = "93 93 93 93 92 91 91 94 94 94 94 94 95 95 95 73 73 73 73 73 73 73";
	string myOutput = compress(myInput);
    
    cout<<myOutput<<endl;
    cout<< uncompress(myOutput) << endl;
    
    return 0;
}

string compress(string & input)
{
    istringstream ss(input);
    ostringstream c;

    int count=1;
    string token, last;

    getline(ss,last,' ');
    while(getline(ss,token,' '))
    {
        if(token == last)
            count++;
        
        else
        {
            if(count >=4)
                c<<"ff "<<last<<" "<<count<<" ";
            else
            {
                for(int i=0; i<count; i++)
                    c<<last<<" ";
            }
            count = 1;
        }
        last = token;
    }

    //prints last input
    if(count >=4)
        c<<"ff "<<last<<" "<<count<<" ";

    else
    {
        for(int i=0; i<count; i++)
            c<<last<<" ";
    }  

    return c.str();
}

string uncompress(string & input)
{
    stringstream ss(input);
    ostringstream c;

    string num, freq;

    while( getline(ss,num,' ') )
    {
        if(num == "ff")
        {
            //number
            getline(ss,num,' ');
            //frequency
            getline(ss,freq,' ');
                int f = atoi(freq.c_str());

            for(int j=0; j < f; j++)
                c<<num<<" ";
        }
        else
            c<<num<<" ";
    }
    
    return c.str();
}
