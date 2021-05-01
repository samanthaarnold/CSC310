#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
using namespace std;

int main()
{

    string s = "BARE";
   
    int r=0;
    int i; 
    for(i=0; i<4; i++)
    {
        r += (int)s[i];
    }
  

    cout<<r<<endl;
}