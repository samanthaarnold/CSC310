// commandline ./update library.out transaction.out update.out
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
void readTransact(TransactionRec & T, string & transactfile,  map<unsigned int, int> & books, int & numTransactions, string & masterfile);
void addRecord(TransactionRec & T, map<unsigned int, int> & books, int & numTransact, string & transactfile);
void deleteRecord(TransactionRec & T, map<unsigned int, int> & books, int & numTransactions, string & transactfile);
void changeOnHand(TransactionRec & T, map<unsigned int, int> & books, int & numTransactions, string & transactfile);
void changePrice(TransactionRec & T, map<unsigned int, int> & books, int & numTransactions, string & transactfile);
bool inMap(map<unsigned int,int> & books, int isbn);
int checkOnhand(TransactionRec & T);
void printLine(TransactionRec & T);
void printMap(map<unsigned int, int> & books);
void printToNewMaster();

int main(int argc, char* argv[])
{
    if(argc ==4)
    {
        string masterfile = argv[1];
        string transactfile = argv[2];
        string newMasterFile = argv[3];
        system("cp library.out copy.out");

        TransactionRec T;
        //stores ISBN and corresponding byte ofset
        map<unsigned int, int> books;
        int numTransactions=0;
        
        readMaster(T, masterfile, books);
        //printMap(books);
        cout<<endl;
        readTransact(T,transactfile,books, numTransactions, masterfile);
        printMap(books);
    }
    else
    {
        cout<<"Incorrect number of arguments entered"<<endl;
    }
    
    

    //read in binary masterfile from create.cpp
        //fstream masterFile(masterfile.c_str(), ios::in|ios::binary);
    //keep records of transactions, open a new binary file
        //fstream transactionFile (transactfile.c_str(), ios::out | ios::binary);
    //make new masterfile with updated records
        //fstream updatedFile (newMasterFile.c_str(), ios::in | ios::binary);
    //txt file that records errors
        //fstream error("ERRORS", ios::out);
   
    return 0;
}

//reads the binary master file from create.cpp and will return a map
//that stores ISBN and corresponding byte offset 
void readMaster(TransactionRec & T, string & masterfile, map<unsigned int,int> & books)
{
    //read in binary masterfile from create.cpp
    fstream masterFile(masterfile.c_str(), ios::in|ios::binary);
    
    //creating map, inserting isbn num and byte offset
    while(masterFile.read( (char *) & T.B, sizeof(T.B)) )
    {
        //cout<<T.B.isbn<<"\t"<<masterFile.tellg()<<endl;
        long mark = masterFile.tellg();
        books[T.B.isbn] = mark;
    }
    printMap(books);
    masterFile.close();
}

void printMap(map<unsigned int,int> & books)
{
    map<unsigned int,int>::iterator itr;
    for(itr = books.begin(); itr != books.end(); ++itr)
    {
        cout << '\t' << itr->first 
             << '\t' << itr->second << '\n'; 
    }

}

void readTransact(TransactionRec & T, string & transactfile,  
    map<unsigned int, int> & books, int & numTransactions, string & masterfile)
{
    fstream transactionFile (transactfile.c_str(), ios::in | ios::binary);
    fstream masterFile(masterfile.c_str(), ios::out|ios::binary);

    //read in information from transaction file

    string todo;
    string records;
    while(transactionFile.read( (char *) & T, sizeof(T)))
    //while(transactionFile >> todo)
    {
        //transactionFile.ignore(1,' ');
        //getline(transactionFile,records);

        //getline()s

        switch (T.ToDo)
        {
            case 0:
                cout<<"adds"<<endl;
                addRecord(T,books, numTransactions, transactfile);
                //printMap(books);
                cout<<"done"<<endl;
                return;
            case 1:
                cout<<"delete"<<endl;
                //deleteRecord(T,books, numTransactions, transactfile);
                break;
            case 2:
                cout<<"changeOnhand"<<endl;
                //changeOnHand(T,books, numTransactions, transactfile);
                break;
            case 3:
                cout<<"changeOnhand"<<endl;
                //changePrice(T,books, numTransactions, transactfile);
                break;
        }
        //NEED to add to map
        //write out to copy of masterfile
        
    
    }
}

bool inMap(map<unsigned int, int> & books, int isbn)
{
    bool output = books.count(isbn)>=1 ? true : false;
    return output;
}

//If ISBN does not exist, add a new record to the new master, containing all the other 
//information in the TransactionRec. If it does exist, print an error message

//suppose it has already been readin from file and stored in BookRec
void addRecord(TransactionRec & T, map<unsigned int, int> & books, int & numTransactions, string & transactfile)
{
    int tempISBN;

    fstream error("ERRORS", ios::out);
    fstream tFile (transactfile.c_str(), ios::in | ios::binary);
    
    numTransactions++;
    
    //new ISBN needs to be added to the map and print information in transaction file
    if(!inMap(books,tempISBN))
    {
        //add to map 
        // GET THE BYTE OFSET FROM MASTERFILE COPY
        books[tempISBN];
    }
    //ISBN already exists
    else
    {
        error<<"Error in transaction number "<<numTransactions<<
            ": cannot add---duplicate key "<<tempISBN<<endl;
    }
}

//If ISBN exists, remove record from map. Do not print to updated master
//If it does not exist, print an error message. 
void deleteRecord(TransactionRec & T, map<unsigned int, int> & books, int & numTransactions, string & transactfile)
{
    int tempISBN;

    fstream error("ERRORS", ios::out);
    fstream tFile (transactfile.c_str(), ios::out | ios::binary);
    
    numTransactions++;
    
    //ISBN needs to be removed from map and print information in transaction file
    if(inMap(books,tempISBN))
    {
        //cout<<"Delete"; printLine(T);
        tFile << "Delete "; printLine(T);

        //remove from map
        books.erase(tempISBN);
        
    }
    //ISBN does not exist in map
    else
    {
        error<<"Error in transaction number "<<numTransactions<<
            ": cannot delete--- no such key "<<tempISBN<<endl;
    }
}

//calculate how many books are in stock, adds and subtracts
int checkOnhand(TransactionRec & T)
{
    int count;
    int newOnHand = count + T.B.onhand;
    cout<<newOnHand<<endl;
    return newOnHand;
}

void changeOnHand(TransactionRec & T, map<unsigned int, int> & books, int & numTransactions, string & transactfile)
{
    //set equal to method checkOnhand
    int newOnHand;

    fstream error("ERRORS", ios::out);
    fstream tFile (transactfile.c_str(), ios::in | ios::binary);
    
    numTransactions++;
    
    //new ISBN needs to be added to the map and print information in transaction file
    if(inMap(books,T.B.isbn))
    {
        //CHECK PRICE HERE 

        //if onHand is negative
        if(newOnHand < 0)
        {
            T.B.onhand = 0;
            error<<"Error in transaction number "<<numTransactions<<
                ": count = "<< newOnHand <<"for key "<<T.B.isbn<<endl;
        }
        else
        {
            T.B.onhand = newOnHand;
            tFile << "ChangeOnhand "; printLine(T);
        }  
    }
    //ISBN does not exist in map
    else
    {
        error<<"Error in transaction number "<<numTransactions<<
            ": cannot change count no such key "<<T.B.isbn<<endl;
    }
}

//checks to see if the ISBN is already in the map, if it is then change the price from the transaction file
//if ISBN is not in the map, then send error message
void changePrice(TransactionRec & T, map<unsigned int, int> & books, int & numTransactions, string & transactfile)
{
    int newPrice;

    fstream error("ERRORS", ios::out);
    fstream tFile (transactfile.c_str(), ios::in | ios::binary);
    
    numTransactions++;
    
    //new ISBN needs to be added to the map and print information in transaction file
    if(inMap(books,T.B.isbn))
    {
        T.B.price = newPrice;
    }
    //ISBN already exists
    else
    {
        //cout<<"Error in transaction number "<<numTransactions<<
            //": cannot add---duplicate key "<<tempISBN<<endl;
        error<<"Error in transaction number "<<numTransactions<<
            ": cannot change price--- no such key "<<T.B.isbn<<endl;
    }
}

void printLine(TransactionRec & T)
{
    cout<<setw(10)<<setfill('0')<<T.B.isbn
	      <<setw(25)<<setfill(' ')<<T.B.name
	      <<setw(25)<<T.B.author
	      <<setw(3)<<T.B.onhand<<setprecision(4)
	      <<setw(6)<<T.B.price
	      <<setw(10)<<T.B.type<<endl;
}

//we have isbn num, and byte ofset. Byte ofset is the end of the line so 
// need find the previous byte ofset and then move till the end of that byte ofset
//use seekp() 
void printToNewMaster()
{

}