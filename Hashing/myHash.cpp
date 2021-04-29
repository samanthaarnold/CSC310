// myHash.cpp

#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
using namespace std;

typedef char String[20];
const int NumCities = 435;

struct Bucket
{
	int currSize;
	String key[3];
};

int hashMe (string key, int maxAddresses);
void numCollisions(int array[]);
void buildHashFile(Bucket mybucks[]);
void flushBuckets(Bucket mybucks[]);
void buildHashArray(fstream& infile, int array[], Bucket mybucks[]);
void printBuckets(Bucket mybucks[]);
int hashSearch (string key, Bucket mybucks[]);

int main()
{
	fstream infile("cities.dat", ios::in);
	int array[300] = {0};
        Bucket mybucks[300];

	flushBuckets(mybucks);
	buildHashArray(infile, array, mybucks);
	numCollisions(array);
	printBuckets(mybucks);
	buildHashFile(mybucks);

	cout << "hashSearch(\"Oakdale\") = "
             << hashSearch("Oakdale", mybucks) << endl;
	cout << "hashSearch(\"Whigham\") = "
             << hashSearch("Whigham", mybucks) << endl;

        return 0;
}

void flushBuckets(Bucket mybucks[])
{
	for (int i = 0;  i < 300;  i++)
	{
		mybucks[i].currSize = 0;
		for (int j = 0;  j < 3;  j++)
			strcpy (mybucks[i].key[j], "///");
	}
}

void buildHashArray(fstream& infile, int array[], Bucket mybucks[])
{
	string s;  int i;

	getline (infile, s);
	while (infile)
	{
		int slot = hashMe(s, 300);
		cout << "Key = " << s << " with a hash val of " << slot << endl;
		array[slot] += 1;
		mybucks[slot].currSize += 1;
		i = 0;
		while(strcmp(mybucks[slot].key[i],"///") != 0)
		{
			i++;
			if (i == 3)
			{
				i = 0;
				cout<<"Overflow at "<<slot<<" on hash of "<<s<< endl;
				slot++;
				if (slot > 299)
					slot = 0;
			}
		}
		strcpy(mybucks[slot].key[i], s.c_str());
		getline (infile, s);
	}
}

void buildHashFile(Bucket mybucks[])
{
	fstream outfile("hash.ind", ios::out | ios::binary);
	for (int i = 0;  i < 300;  i++)
		outfile.write((char *) &mybucks[i], sizeof(Bucket));
}

void numCollisions(int array[])
{
	int synonymns = 0;
	for (int j = 0;  j < 300;  j++)
	{
		if (array[j] > 1)
			synonymns += array[j] - 1;
	}
	cout << "Total Synonyms = " << synonymns << endl;

	cout.setf(ios::fixed, ios::floatfield);  cout.setf(ios::showpoint);
	for (int i=0;  i <= 7;  i++)
	{
		int count = 0;
		cout << "d(" << i << ") = ";
		for (int j = 0;  j < 300;  j++)
			if (array[j] == i)
				count++;
		cout << setprecision(2) << count << " " << float(count) / 300.0 << endl;
	}
}

int hashMe (string key, int maxAddresses)
{
	// Post:  Folds string key into an integer and returns it
	
	//make copy
	string copy = key;
	
	for(int i=0; i<copy.size(); i++)
	{
		int copy_ascii = int(copy[i]);
		//lowercase letters
		if(copy_ascii>95)
		{
			copy_ascii -=32;
		}
		

	}
	

}

int hashSearch (string key, Bucket mybucks[])
{
	// Searches for string key in your array of buckets using strcmp.
	// Pre :  Array of 300 buckets each of size 3 has been initialized
	// Post : Returns the the number of probe checks needed to find key


        // Find the location your key hashes to in your array by calling hashMe.  Print out that location.


        
        // Use a while loop that continues until it finds key.  Return number of checks to find.
        // Otherwise, return a -1.
        


}
 
void printBuckets(Bucket mybucks[])
{
	// Pre:  Our array of 300 buckets size 3 has been initialized
	// Post:  Our array is printed out on 300 lines, with the 3 keys inside each bucket per line




	
}
