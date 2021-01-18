//Implement Linux command tail -n, where n is the number of lines from the end of a text file to be copied to the screen
#include<iostream>
#include<string>
#include<fstream>
#include <sstream>
#include<stack>

using namespace std;

void PrintStack(stack<char> c);
int StringToInt(string n);
stack<char> tail(string fileName, int numLinesPrint);

//change ./a.out too tail by "mv ./a.out tail"

int main(int argc, char **argv)
{
    if(argc==3)
    {
        //num of lines to print from tail of file
        string n = argv[1];
        string fileName = argv[2];
        
        //convert string to int and tells us how many lines
        // starting from the botttom to print
        int numLinesPrint = StringToInt(n);
        
        //add the lines from the bottom of text file to a stack
        stack<char> t = tail(fileName, numLinesPrint);
       
        //print stack
        PrintStack(t);
        cout<<endl;
    }
    else
        cout<<"Please enter the correct number of arguments"<<endl;
    
    return 0;
}

void PrintStack(stack<char> c)
{
    while(!c.empty())
    {
        cout<<c.top();
        c.pop();
    }
}

int StringToInt(string n)
{
    //removes '-' from string
    string lines = n.substr(1);
        
    //convert string to int using stringstream
    stringstream s(lines);
    int numLines = 0;
    s >> numLines;
    
    return numLines;
}

stack<char> tail(string fileName, int numLinesPrint)
{
    //open file for input and output 
    //(maybe don't need to open it for output)?
    fstream inOut (fileName.c_str(), ios::in | ios::out);

    //starts at the last char at end of txt file 
    inOut.seekg(0, ios::end);

    //j starts at 1 because you can't have neg. 0
    int j = 1;
    int line = 0;
    char token;
    stack <char> c;
    
    //outer while loop is keeping track of how many lines to print
    while(line != numLinesPrint)
    {
        //inner while loop adds chars to stack and stops at '\n'
        while(token != '\n')
        {
            inOut.seekg(-j,ios::end);
            inOut.get(token);
            c.push(token);
            j++;
        }
        //resets token when it is newline
        //so it can enter inner while loop
        if(token == '\n')
        {
            token = ' ';
        }
        line++;
    }
    return c;
}

