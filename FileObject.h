#ifndef FILEOBJECT_H
#define FILEOBJECT_H

#include <string>
using namespace std;

#include <sys/stat.h>

#include "Utilities.h"

typedef struct stat FileStats;


class FileInfo
{
protected:
    string pFullPath;
    unsigned int  pDateModified;
    unsigned long pFileSize;
    unsigned int pPermissions;
    int getStats(string);

public:
    FileInfo();
    virtual int getData(string);
    virtual int DeleteFile(string);

    string FullPath()
    {
        return pFullPath;
    }

    unsigned int  DateModified()
    {
        return pDateModified;
    }

    unsigned long FileSize()
    {
        return pFileSize;
    }

    unsigned int Permissions()
    {
        return pPermissions;
    }
};

class FileReader : public FileInfo
{
protected:
    string pContent;

public:
    FileReader();
    virtual int getData(string);

    string Content()
    {
        return pContent;
    }
};

class FileWriter
{
protected:
    string pFullPath;
    string Content;

public:

    FileWriter(string);
    int Write(string);

    string FullPath()
    {
        return pFullPath;
    }
};

#endif

