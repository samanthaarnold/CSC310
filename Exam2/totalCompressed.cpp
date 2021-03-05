#include<iostream>
#include<string>
#include<string.h> 
#include <sstream>
#include <cstdlib>
#include <utility>

using namespace std;

string compress(string & input);
string uncompress(string & input);
int totalCompressed(string & input);
int hexToDec(char hexVal[]);

int main(int argc, char **argv)
{
    string myInput = "93 93 93 93 92 91 91 94 94 94 94 94 95 95 95 73 73 73 73 73 73 73";
	string myOutput = compress(myInput);
    
    //cout<<myOutput<<endl;
    //cout<< uncompress(myOutput) << endl;

    string comp = "ff 93 04 92 91 91 ff 94 1A";
    cout<<totalCompressed(comp)<<endl;
    //char hexNum[] = "1A";     
    //cout << hexToDec(hexNum) << endl; 
    
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

int totalCompressed(string & input) 
{
    stringstream ss(input);
    //string c;
    string num, freq;
    int totalComp = 0;

    while( getline(ss,num,' ') ) 
    {
        if(num == "ff")
        {
            //number
            getline(ss,num,' ');
            
            //frequency
            getline(ss,freq,' ');
            
                //convert hex to decimal num
                char hexVal[freq.length() + 1];
                strcpy(hexVal, freq.c_str());

                int f = hexToDec(hexVal);
                //cout<<"freq: "<<f<<endl;
                totalComp += f;
                /*
                for(int j=0; j < f; j++)
                    c += (num+" ");
                */
        }
        else
        {
            //cout<<"freq: 1"<<endl;
            //c+= (num+" ");
            totalComp += 1;
        }    
    }
    //cout<<c<<endl;
    return totalComp;
}

int hexToDec(char hexVal[]) 
{
    int len = strlen(hexVal); 
      
    // Initializing base value to 1, i.e 16^0 
    int base = 1; 
      
    int dec_val = 0; 
      
    // Extracting characters as digits from last character 
    for (int i=len-1; i>=0; i--) 
    {    
        // if character lies in '0'-'9', converting  
        // it to integral 0-9 by subtracting 48 from 
        // ASCII value. 
        if (hexVal[i]>='0' && hexVal[i]<='9') 
        { 
            dec_val += (hexVal[i] - 48)*base; 
                  
            // incrementing base by power 
            base = base * 16; 
        } 
  
        // if character lies in 'A'-'F' , converting  
        // it to integral 10 - 15 by subtracting 55  
        // from ASCII value 
        else if (hexVal[i]>='A' && hexVal[i]<='F') 
        { 
            dec_val += (hexVal[i] - 55)*base; 
          
            // incrementing base by power 
            base = base*16; 
        } 
    } 
      
    return dec_val; 
} 
