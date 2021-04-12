#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int convertTime(string & time);

int main(int argc, char **argv){

    string t = "2:30";
    cout<<convertTime(t)<<endl;
    return 0;
}

int convertTime(string & time){
    stringstream ss(time);
    int min, sec;
    char delim;
    ss >> min >> delim >> sec;
    //cout<<min<<" "<<sec<<endl;
    min*=60;
    sec+=min;
    
    return sec;
}