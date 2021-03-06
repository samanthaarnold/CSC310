#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <climits>

using namespace std;

typedef	char String[25];

struct BookRec
{
  unsigned int isbn;
  String name;
  String author;
  int onhand;
  float price;
  String type;
};

bool IllegalNumber(long tempISBN, int lineNum);
bool NumberOutOfSequence(long tempISBN, int lineNum, long prevISBN, BookRec & temp);
bool IllegalOnHandOrPrice(int lineNum, BookRec & temp);
void read(BookRec & temp);
void printLine(BookRec & temp);
void output(BookRec & temp);

int main(int argc, char* argv[])
{
    //check number of arguments
    if(argc == 1)
    {
        cout<<endl;
        BookRec temp;
        read(temp);
        cout<<endl;
        for (int i=0; i<80; i++) cout<<'*';
        output(temp);
        
        for (int i=0; i<80; i++) cout<<'*'; cout<<endl;
    }

    return 0;
}

//read file 
void read(BookRec & temp)
{
    fstream infile("library.dat", ios::in);
    fstream outfile ("library.out", ios::out | ios::binary);

    string copies, price;
    long tempISBN;
    int lineNum;
    unsigned int prevISBN;

    while (infile >> tempISBN)
    {
        bool output = true;
        lineNum++;
    
        infile.ignore(1,'|');
        
        //checks isbn number here, will not be sent to outfile
        if( !IllegalNumber(tempISBN, lineNum) )
        {
            output=false;
            string error;
            getline(infile,error);
        }
        
        else 
        {
            temp.isbn = tempISBN;
            infile.getline(temp.name, 25, '|');
            infile.getline(temp.author, 25, '|');
            //reads in as string, and then converts it to int
            getline(infile,copies,'|');
                temp.onhand = atoi(copies.c_str());
            //reads in as string, and then converts it to int
            getline(infile,price,'|');
                temp.price = atof(price.c_str());
            infile.getline(temp.type, 25, '\n');   
            
            //placed after because need to print line
            // will not be sent to outfile
            if(!IllegalOnHandOrPrice(lineNum, temp))
            {
                output = false;
            }

            //still needs to be sent to outfile
            NumberOutOfSequence(tempISBN, lineNum, prevISBN, temp);
        }
        
        if(output)
        {
            outfile.write( (char *) & temp, sizeof(BookRec) );
            tempISBN = prevISBN;
        } 
    }
    infile.clear();
    outfile.close();
}

//print method from Dr. Digh
void printLine(BookRec & temp)
{
    cout<<setw(10)<<setfill('0')<<temp.isbn
	      <<setw(25)<<setfill(' ')<<temp.name
	      <<setw(25)<<temp.author
	      <<setw(3)<<temp.onhand;
            printf("%6.2f", temp.price);
	      cout<<setw(10)<<temp.type<<endl;
}

//Ignores isbn number when it is less than 1, displays an error
// message to cerr and record should be ignored.
bool IllegalNumber(long tempISBN, int lineNum)
{
    if(tempISBN < -1)
    {
        cout<<"> Illegal isbn number encountered on line "<<lineNum<<" of data file- record ignored."<<endl;
        return false;
    }
    else
    {
        return true;
    }
}

//If isbn is <= to previous isbn, displays error message to cerr
// and record should be written out to cout. Record should be 
// added to output file.
bool NumberOutOfSequence(long tempISBN, int lineNum, long prevISBN, BookRec & temp)
{
    if(tempISBN <= prevISBN)
    {
        cout<<"> Isbn number out of sequence on line "<<lineNum<<" of data file"<<endl;
        printLine(temp);
        return false;
    }
    else
    {
        return true;
    }
}

//If either of the fields is < 0, it is considered illegal and
// an error message should be written to cerr and the illegal
// record should be written to cout. Record should be ignored.
bool IllegalOnHandOrPrice(int lineNum, BookRec & temp)
{
    if(temp.price < 0 || temp.onhand < 0)
    {
        cout<<"> Negative amount onhand on line "<<lineNum<<" of data file- record ignored."<<endl;
        printLine(temp);
        return false;
    }
    else
    {
        return true;
    }
}

//print records to screen from binary file 
void output(BookRec & temp)
{
    fstream binfile("library.out", ios::in | ios::binary);
    cout<<endl;
    while(binfile.read( (char *) & temp, sizeof(temp)) )
    {
        printLine(temp);
    }
    binfile.close();
}