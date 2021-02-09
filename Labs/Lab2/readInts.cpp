#include <fstream>
#include <iostream>

using namespace std;

int file(fstream & inFile);

int main(int argc, char* argv[])
{
    fstream inFile(argv[1], ios::in);
    
    int sum = file(inFile);

    if(sum != -1)
        cout<<"Sum: "<<sum<<endl;
    else
        cout<<"File is not in correct format"<<endl;
    
    inFile.close();
    return 0;
}

int file(fstream & inFile)
{
    int temp, sum=0;
    
    //checks to make sure beginning of file starts with ints
    while(!isdigit(inFile.peek()))
        inFile.ignore();
    
    while (inFile >> temp)
    {
        //cout<<"temp: "<<temp<<endl;
        sum+=temp;
        
        //checks if next input is a char and not end of file
        if(!isdigit(inFile.peek()) && inFile.peek() != EOF)
        {
            //skips over commas, new lines, and spaces
            if(inFile.peek() ==',' || inFile.peek() =='\n' || inFile.peek() ==' ')
                inFile.ignore();
            
            else
            {
                sum = -1;
                break;
            } 
        }
    } 
    return sum;
}