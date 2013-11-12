#ifndef FILEOBJECT_H
#define FILEOBJECT_H

#include <string>
using namespace std;

#include <sys/stat.h>

typedef struct stat FileStats;


class FileInfo
{
protected:
    string pFullPath;
    string pDateModified;
    unsigned long pFileSize;
    unsigned int pPermissions;
    int getStats(string);

public:
    FileInfo();
    virtual int getData(string);
    string FullPath();
    string DateModified();
    unsigned long FileSize();
    unsigned int Permissions();
};

class FileObject : public FileInfo
{
protected:
    string pContent;

public:
    FileObject();
    int getData(string);
    string Content();
};

#endif

