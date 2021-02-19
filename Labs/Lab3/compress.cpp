#include<iostream>
#include<string>
#include <sstream>
#include <cstdlib>
#include <utility>

using namespace std;

void compress(string & input);
void uncompress(string & input);

int main(int argc, char **argv)
{
    string myInput = "93 93 93 93 92 91 91 94 94 94 94 94 95 95 95 73 73 73 73 73 73 73";
	compress(myInput);
    cout<<endl;
    
    string myOutput = "ff 93 04 92 91 91 ff 94 05 95 95 95 ff 73 07";
    uncompress(myOutput);
    cout<<endl;
    
    return 0;
}

void compress(string & input)
{
    stringstream ss(input);

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
                cout<<"ff "<<last<<" "<<count<<" ";

            else
            {
                for(int i=0; i<count; i++)
                    cout<<last<<" ";
            }
            count = 1;
        }
        last = token;
    }

    //prints last input
    if(count >=4)
        cout<<"ff "<<last<<" "<<count<<" ";

    else
    {
        for(int i=0; i<count; i++)
            cout<<last<<" ";
    }  
}

void uncompress(string & input)
{
    stringstream ss(input);

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
                cout<<num<<" ";
        }
        else
            cout<<num<<" ";
    }
}
