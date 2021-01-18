//Implement Linux command wc -c,-l,-w where c is the byte count, -l is the newline count, -w is word count
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void wc(char **argv, string fileName);
void arguments(char **argv, string fileName);
void wordCount(char **argv, string fileName);
void byteCount(char **argv, string fileName);
void newLineCounts(char **argv, string fileName);

//change ./a.out too tail by "mv ./a.out wc"

int main(int argc, char **argv)
{  
    
    if(argc==3)
    {
        string fileName = argv[2];
        arguments(argv,fileName);
    }
    else if(argc==2)
    {
        string filename = argv[1];
        wc(argv, filename);
    }
    else
    {
        cout<<"Please enter the correct number of arguments"<<endl;
    }

    return 0;
}

void arguments(char **argv, string fileName)
{
    string arg = argv[1];
    //prints byte counts
    if(arg == "-c")
        byteCount(argv, fileName);
    
    //prints newline counts
    if(arg == "-l")
        newLineCounts(argv, fileName);
    
    //prints word counts
    if(arg == "-w")
        wordCount(argv, fileName);
}

void wc(char **argv, string fileName)
{
    //open file for input and output 
    //(maybe don't need to open it for output)
    fstream inOut (fileName.c_str(), ios::in | ios::out);
    
    int charCount = 0;
    //wordCount set to 1 because file could possibly
    //not include any spaces or new lines
    int wordCount = 1;
    //assume newline at the end of file for linux
    //operating systems
    int newLineCount = 0;
    char ch;
    
    //set byte offset to beginning of file
    inOut.seekg(0);
    
    while( inOut.get(ch))
    {
        charCount++;
        if( ch == '\n' )
            newLineCount++;
        if( ch == ' ' || ch == '\n')
            wordCount++;
    }
    cout<<" "<<newLineCount<<" "<<wordCount<<" "<<charCount<<" "<<fileName<<endl;
}

void byteCount(char **argv, string fileName)
{
    //open file for input and output 
    //(maybe don't need to open it for output)
    fstream inOut (fileName.c_str(), ios::in | ios::out);
    
    int charCount = 0;
    char ch;
    
    //set byte offset to beginning of file
    inOut.seekg(0);

    while( inOut.get(ch))
        charCount++;

    cout<<" "<<charCount<<" "<<fileName<<endl;
}

void newLineCounts(char **argv, string fileName)
{
    //open file for input and output 
    //(maybe don't need to open it for output)
    fstream inOut (fileName.c_str(), ios::in | ios::out);
    
    //assume newline at the end of file for linux
    //operating systems
    int newLineCount = 0;
    char ch;
    
    //set byte offset to beginning of file
    inOut.seekg(0);
    
    while( inOut.get(ch))
    {
        if( ch == '\n' )
            newLineCount++;
    }
    cout<<" "<<newLineCount<<" "<<fileName<<endl;
}

void wordCount(char **argv, string fileName)
{
    //open file for input and output 
    //(maybe don't need to open it for output)
    fstream inOut (fileName.c_str(), ios::in | ios::out);
    
    //wordCount set to 1 because file could possibly
    //not include any spaces or new lines
    int wordCount = 1;
    char ch;
    
    //set byte offset to beginning of file
    inOut.seekg(0);
    
    while( inOut.get(ch))
    {
        if( ch == ' ' || ch == '\n')
            wordCount++;
    }
    cout<<" "<<wordCount<<" "<<fileName<<endl;
}
