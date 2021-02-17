#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;
    
string convertMonthToInt(string & month);

int main(int argc, char* argv[]) 
{
    fstream inFile(argv[1], ios::in);
    
    string month, day, year, date;
    
    //reads in month
    getline(inFile, month, ' ');
        date += convertMonthToInt(month);
    //reads in the date
    getline(inFile, day, ',');
        date+=day;
    //reads in year
    inFile >> year;
        date+=year;
   
    inFile.close();

    //convert string to long
    long canonical = atol(date.c_str());
    cout<<canonical<<endl;
}

//Converts month to corresponding integer value. Compare month to array of 
// months, and the position+1 is the corresponding integer value
string convertMonthToInt(string & month)
{
    string position;
    
    string months[] = {"January", "February", "March", "April", "May", "June", 
        "July", "August", "September", "October", "November", "December"}; 
    
    int i=0;
    while(month != months[i]){ i++; }

    //use string stream to convert int to string
    ostringstream ss;   
    ss << i+1;      
    return position = ss.str();
    istringstream ss;
    
}


