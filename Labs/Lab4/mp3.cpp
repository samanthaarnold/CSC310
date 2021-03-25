#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

class Song {
public:
  string title;
  int time;
  int track;      // Primary key
  bool operator < (Song another) const { return title < another.title;} //if(s < s1)
}; 

//print a song
ostream & operator << (ostream& out, Song & l) {     
        cout << l.track << ".  " << l.title << " " << l.time/100 << ":";
        if ((l.time % 100) < 10) cout << "0";
        cout << l.time % 100;
        return out;
}

class Album {
  public :
    map<int, Song> songs;   //refernece song inside an album, int is track
    string name;  // Album's name
    string artist;
    string genre;
    int time;     // Total time of all songs on album
    int nsongs;   // Total number of songs on album
};

class Artist {
   public :
     string name; // Artist's name
     int time;    // Total time of all songs on all albums by this artist
     int nsongs;  // Total number of songs on all albums by this artist
     bool operator < (Artist another) const { return name < another.name;}
};

Artist updateArtist(vector<Artist> & artists, string & artist);
string removechar(string & text);
bool AlbumInMMap(multimap<Artist,Album> & mmap, string & tempAlbum);

typedef multimap<Artist,Album>::value_type val;

int main(int argc, char **argv)
{
  //read in music text file
  fstream infile(argv[1], ios::in);
  
  //declare multimap<Artist, Album>
  multimap<Artist,Album> mmap;

  Song s; 
  Album alb;
  Artist a; 
 
 string title;
  while(infile >> title)
  {
    cout<<removechar(title)<<" ";
   
    //time
    string min, sec;
    getline(infile,min,':');
    getline(infile,sec,' ');
    //infile >> sec;
    string time = min + sec;
    s.time += stoi(time);
    cout<<s.time<<" ";
    
    //artist
    string artName;
    infile >> artName;
    //a.name = removechar(artName);
    cout<<a.name<<" ";

    //album
    string albumName;
    infile >> albumName;
    cout<<removechar(albumName)<<" ";
    

    //genre
    string genre;
    infile >> genre;
    cout<<genre<<" ";
    
    //track
    infile >> s.track;
    cout<<s.track<<endl;
    
    /*
    
    //update Album object with new song, time, and nsong
    alb.songs[s.track] = s;
    alb.name = removechar(albumName);
    alb.artist = removechar(artName);
    alb.genre = genre;
    alb.time += stoi(time);
    alb.nsongs += 1;
   
    //update Artist object with time and nsong
    

    //add Album to multimap
    if(!AlbumInMMap(mmap, albumName))
    {

      mmap.insert(val(a,alb));
    }
    */
  }
  infile.close();
 
}

bool AlbumInMMap(multimap<Artist,Album> & mmap, string & tempAlbum)
{
  multimap<Artist,Album> :: iterator itr;
  for (itr = mmap.begin(); itr != mmap.end(); ++itr)
  {
    if(itr->second.name == tempAlbum)
    {
      return true;
    }
  }
  //not in mmap
  return false;
}

string removechar(string & text)
{
  replace(text.begin(), text.end(), '_', ' ');
  return text;
}
