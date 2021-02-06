#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include <map>

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

enum TransactionType{Add, Delete, ChangeOnhand, ChangePrice};

struct TransactionRec
{
    TransactionType ToDo;
    BookRec B;
};

void readMaster(TransactionRec & T, string & masterfile,  map<unsigned int,int> & books);
void readTransact(TransactionRec & T, string & transactfile,  map<unsigned int, int> & books,
 int & numTransactions, string & masterfile);
void addRecord(TransactionRec & T, map<unsigned int, int> & books, int & numTransact, fstream & masterFile);
void deleteRecord(TransactionRec & T, map<unsigned int, int> & books, int & numTransactions);
void changeOnHand(TransactionRec & T, map<unsigned int, int> & books, int & numTransactions, fstream & masterFile);
void changePrice(TransactionRec & T, map<unsigned int, int> & books, int & numTransactions, 
int & newPrice, fstream & masterFile);
bool inMap(map<unsigned int,int> & books, int isbn);
void printMap(map<unsigned int, int> & books);
void printToNewMaster(TransactionRec & T, map<unsigned int, int> & books, string & newMasterFile);
void printLine(TransactionRec & T);

int main(int argc, char* argv[])
{
    if(argc ==4)
    {
        //library.out
        string masterfile = argv[1];
        //transact.out
        string transactfile = argv[2];
        //update.out
        string newMasterFile = argv[3];
        
        //creates a copy of library so masterfile cannot be altered
        system("cp library.out copy.out");

        TransactionRec T;
        //stores ISBN and corresponding byte ofset
        map<unsigned int, int> books;
        int numTransactions=0;
        
        readMaster(T, masterfile, books);
        readTransact(T,transactfile,books, numTransactions, masterfile);
        for (int i=0; i<80; i++) cout<<'*'; cout<<endl;
        printToNewMaster(T,books,newMasterFile);
        for (int i=0; i<80; i++) cout<<'*'; cout<<endl;
        system("rm copy.out");
    }
    else
    {
        cout<<"Incorrect number of arguments entered"<<endl;
    }
    return 0;
}

//reads the binary master file from create.cpp and will return a map
//that stores ISBN and corresponding byte offset 
void readMaster(TransactionRec & T, string & masterfile, map<unsigned int,int> & books)
{
    //read in binary masterfile from create.cpp
    fstream masterFile("copy.out", ios::in|ios::binary);
   
    //creating map, inserting isbn num and byte offset
    while(masterFile.read( (char *) & T.B, sizeof(T.B)) )
    {
        long mark = masterFile.tellg();
        books[T.B.isbn] = mark;
    }
    masterFile.close();
    masterFile.clear();
}

//create iterator to print what is in map
void printMap(map<unsigned int,int> & books)
{
    map<unsigned int,int>::iterator itr;
    for(itr = books.begin(); itr != books.end(); ++itr)
    {
        cout << '\t' << itr->first 
             << '\t' << itr->second << '\n'; 
    }
}

//reads transact file and and adds, deletes, changes onHand and price
void readTransact(TransactionRec & T, string & transactfile,  
    map<unsigned int, int> & books, int & numTransactions, string & masterfile)
{
    fstream transactionFile (transactfile.c_str(), ios::in | ios::binary);
    fstream masterFile("copy.out", ios::in|ios::out|ios::binary);

    //read in information from transaction file    
    while(transactionFile.read( (char *) & T, sizeof(TransactionRec)))
    {
        int newOnHand = T.B.onhand;
        int newPrice = T.B.price;

        switch (T.ToDo)
        {
            case 0:
                addRecord(T,books, numTransactions, masterFile);
                break;
            case 1:
                deleteRecord(T,books, numTransactions);
                break;
            case 2:
                changeOnHand(T,books, numTransactions, masterFile);
                break;
            case 3:
                changePrice(T,books, numTransactions, newPrice, masterFile);
                break;
        }
    }
    transactionFile.close();
    masterFile.close();
    masterFile.clear();
}

//checking to see if ISBN is in map
//we know its in the map if the count is greater than 1
bool inMap(map<unsigned int, int> & books, int isbn)
{
    bool output = books.count(isbn)>=1 ? true : false;
    return output;
}

//If ISBN does not exist, add a new record to the new master, containing all the other 
//information in the TransactionRec. If it does exist, print an error message
void addRecord(TransactionRec & T, map<unsigned int, int> & books, int & numTransactions, fstream & masterFile)
{
    numTransactions++;
    
    //new ISBN needs to be added to the map
    if(!inMap(books,T.B.isbn))
    {
        //add ISBN and other information to copy of masterfile
        masterFile.seekp(0,ios::end);
        masterFile.write( (char *) & T.B, sizeof(T.B));
       
        //add to map and mark position of end of line
        long mark = masterFile.tellg();
        books[T.B.isbn] = mark;
    }
    //ISBN already exists
    else
    {
        fstream error("ERRORS", ios::app | ios::out);
        error<<"Error in transaction number "<<numTransactions<<
            ": cannot add---duplicate key "<<T.B.isbn<<endl;
        error.close();
        error.clear();
    }
}

//If ISBN exists, remove record from map. Do not print to updated master
//If it does not exist, print an error message. 
void deleteRecord(TransactionRec & T, map<unsigned int, int> & books, int & numTransactions)
{
    numTransactions++;
    
    //ISBN needs to be removed from map
    if(inMap(books,T.B.isbn))
    {
        books.erase(T.B.isbn);
    }
    //ISBN does not exist in map
    else
    {
        fstream error("ERRORS", ios::app | ios::out);
        error<<"Error in transaction number "<<numTransactions<<
            ": cannot delete--- no such key "<<T.B.isbn<<endl;
        error.close();
        error.clear();
    }
}

void changeOnHand(TransactionRec & T, map<unsigned int, int> & books, int & numTransactions, fstream & masterFile)
{
    numTransactions++;

    //declaring variable for number bookcount
    int tranactOnhand =T.B.onhand;
    
    //setting byte counter to beginning of isbn stored in map
    masterFile.seekp(books[T.B.isbn]-sizeof(T.B), ios::beg);
    masterFile.read( (char *) & T.B, sizeof(T.B) );
    
    //finding the onhand from copy of masterFile
    int oldOnhand = T.B.onhand;
    
    //finding newOnhand amount
    int newOnhand = tranactOnhand+oldOnhand;

    fstream error("ERRORS", ios::app | ios::out);

    //check to see if ISBN is in the map
    if(inMap(books,T.B.isbn))
    {   
        //if onHand value is negative, print error and set onhand to 0
        if(newOnhand < 0)
        {
            T.B.onhand = 0;
            masterFile.seekp(books[T.B.isbn]-sizeof(T.B), ios::beg);
            masterFile.write( (char *) & T.B, sizeof(T.B) );
            error<<"Error in transaction number "<<numTransactions<<
                ": count = "<< newOnhand <<" for key "<<T.B.isbn<<endl;
        }
        else
        {
            T.B.onhand = newOnhand;
            //writing over new onhand amount to copy of masterfile
            masterFile.seekp(books[T.B.isbn]-sizeof(T.B), ios::beg);
            masterFile.write( (char *) & T.B, sizeof(T.B) );
        }  
    }
    //ISBN does not exist in map
    else
    {
        error<<"Error in transaction number "<<numTransactions<<
            ": cannot change count no such key "<<T.B.isbn<<endl;
    }
    error.close();
    error.clear();
}

//checks to see if the ISBN is already in the map, if it is then change the price from the transaction file
//if ISBN is not in the map, then send error message
void changePrice(TransactionRec & T, map<unsigned int, int> & books, int & numTransactions, int & newPrice, fstream & masterFile)
{
    numTransactions++;
    
    //new ISBN needs to be added to the map and print information in transaction file
    if(inMap(books,T.B.isbn))
    {
        masterFile.seekp(books[T.B.isbn]-sizeof(T.B), ios::beg);
        masterFile.read( (char *) & T.B, sizeof(T.B) );
        T.B.price = newPrice;
        //changing price on copy of masterfile
        masterFile.seekp(books[T.B.isbn]-sizeof(T.B), ios::beg);
        masterFile.write( (char *) & T.B, sizeof(T.B) );
    }
    //ISBN already exists
    else
    {
        fstream error("ERRORS", ios::out);
        error<<"Error in transaction number "<<numTransactions<<
            ": cannot change price--- no such key "<<T.B.isbn<<endl;
        error.close();
    }
}

//we have isbn num, and byte ofset. Byte ofset is the end of the line so 
// subtract sizeof line to get to beginning of line and set seekg there
void printToNewMaster(TransactionRec & T, map<unsigned int, int> & books, string & newMasterFile)
{
    fstream masterFile("copy.out", ios::in|ios::binary);
    fstream update(newMasterFile.c_str(), ios::in|ios::out|ios::binary);
    map<unsigned int,int>::iterator itr;
    //create iterator to go through map and get byte values
    for(itr = books.begin(); itr != books.end(); ++itr)
    {
        //given the byte count at the end of the line, move seekg to beginning of the line and read
        masterFile.seekg(itr->second - sizeof(T.B), ios::beg);
        masterFile.read( (char *) & T.B, sizeof(T.B) );
        //write to updated binary file and print to screen
        update.write( (char *) & T.B, sizeof(T.B) );
        printLine(T);   
    }
    update.close();
    masterFile.close();
}

//print method from Dr. Digh
void printLine(TransactionRec & T)
{
    cout<<setw(10)<<setfill('0')<<T.B.isbn
	      <<setw(25)<<setfill(' ')<<T.B.name
	      <<setw(25)<<T.B.author
	      <<setw(3)<<T.B.onhand;
            printf("%6.2f", T.B.price);
	      cout<<setw(10)<<T.B.type<<endl;
}
