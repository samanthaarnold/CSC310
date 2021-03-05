#include<iostream>
#include<fstream>

using namespace std;

void perumtation(string a, int l, int r);

int main() 
{
    string str = "ABC";
    int n = str.length();

    perumtation(str,0,n-1);
    return 0;
}

void perumtation(string a, int l, int r) 
{
    if(l == r) 
    {
        cout<<a<<endl;
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            //cout<<"l: "<<l<<endl;
            swap(a[l],a[i]);
            //cout<<"swap1: "<<a<<endl;

            perumtation(a,l+1,r);

            swap(a[l],a[i]);
            //cout<<"swap2: "<<a<<endl;
        }
        
    }
    
}