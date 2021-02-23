
#include "file.h"

bool File::isADir() const
{
	return ADir;
}

void File::flagAsDir()
{
	ADir = true;
}

int File::recordSize() const
{
	return (strlen(name)+strlen(pmode)+strlen(size)+strlen(stamp));
}

string File::getName() const
{
	return name;
}

string File::getPmode() const
{
	return pmode;
}

string File::getStamp() const
{
	return stamp;
}

string File::getSize() const
{
	return size;
}

//Default Constructor
File::File ()
{
       strcpy (name, "\0");  strcpy (pmode, "\0");
       strcpy (size, "\0"); strcpy (stamp, "\0");
       ADir = false;

}

File::File (const char myName[], const char myPmode[],
            const char mySize[], const char myStamp[])
{
       strcpy (name, myName);  strcpy (pmode, myPmode);
       strcpy (size, mySize); strcpy (stamp, myStamp);
       ADir = false;
}

//opperator overloading with deep copy
File & File::operator = (const File& otherFile)
{
       strcpy (name, otherFile.name);
       strcpy (pmode, otherFile.pmode);
       strcpy (size, otherFile.size);
       strcpy (stamp, otherFile.stamp);
       ADir = otherFile.ADir;
       return *this;
}

//copy constructor
File::File (const File& otherFile)
{
       strcpy (name, otherFile.name);
       strcpy (pmode, otherFile.pmode);
       strcpy (size, otherFile.size);
       strcpy (stamp, otherFile.stamp);
       ADir = otherFile.ADir;
}
