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
    string myInput = "93 93 93 93 92 91 91 94 94 94 94 95 95 95 73 73 73 73 73 73 73";

    compress(myInput);
    
    return 0;
}

void compress(string & input)
{
    stringstream ss(input);
    int count=0;
    string token, prev;
    
    ss >> prev;
    while(ss >> token)
    {
        //ss >> next;
        cout<<"prev "<<prev<<"\t"<<"next "<<token<<endl;
        if(token == prev)
        {
            count++;
            cout<<"same "<<count<<endl;
            prev=token;
        }
        else
        {
            count=0;
        }
        
        //cout<<token<<"\t"<<next<<endl;
    }

    

    
}

void uncompress(string & input)
{
    stringstream ss(input);
    //vector< pair<int,int> > v;

    //map<int, int> m;
    int num;
    string token;
    
    while(getline(ss, token, ' '))
    {
        num = atoi(token.c_str());
        //counts frequency of numbers from string and adds to map
       // m.find(num) == m.end() ? m[num]=1 : m[num]++ ;
    }
}