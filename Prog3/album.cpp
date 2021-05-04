#include "album.h"
#include<iostream>

//copy constructor (deep copy)
Album::Album (const Album& otherAlbum)
{
    strcpy (UPC, otherAlbum.UPC);
    strcpy (Artist, otherAlbum.Artist);
    strcpy (Title, otherAlbum.Title);
}

//
Album::Album (String upc, String artist, String title)
{
    strcpy (UPC, upc);
    strcpy (Artist, artist);
    strcpy (Title, title);
}

//default constructor
Album::Album ()
{
    strcpy (UPC, "\0"); 
    strcpy (Artist, "\0"); 
    strcpy (Title, "\0");
}

//operator overloading with deep copy     
Album & Album::operator = (const Album& otherAlbum)
{
    strcpy (UPC, otherAlbum.UPC);
    strcpy (Artist, otherAlbum.Artist);
    strcpy (Title, otherAlbum.Title);
    return *this;
}

//UPC is like an ISBN num for songs
//operator overloading for comparing UPC's
bool operator < (const Album& a, const Album& b)
{
    return a.getUPC() < b.getUPC();
} 

bool operator == (const Album & a, const Album & b)
{
    if(a.UPC == b.UPC)
        return true;
    return false;
}

istream & operator >> (istream & stream, Album & C)
{
    stream.getline(C.UPC,50);
    stream.getline(C.Artist,50);
    stream.getline(C.Title,50);

    return stream;
}

ostream & operator << (ostream & stream, Album & C)
{
    return stream<<C.UPC<<"|"<<C.Artist<<"|"<<C.Title<<"|"; 
}

//getter function
string Album::getUPC() const
{
    return UPC;
}

//getter function
int Album::recordSize()
{
    return (strlen(UPC)+strlen(Artist)+strlen(Title));
}