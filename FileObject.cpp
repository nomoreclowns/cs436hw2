#include <iostream>
#include <string>
#include <cerrno>
#include <fstream>
using namespace std;
#include <sys/stat.h>
#include "FileObject.h"

FileInfo::FileInfo()
{
    pFullPath="";
    pDateModified="";
}

int FileInfo::getStats(string pathname)
{
  FileStats *resourceInfoPtr = new FileStats();
  int errorCode =  stat(pathname.c_str(), resourceInfoPtr);

  if(errorCode == 0)
  {
      pDateModified = resourceInfoPtr->st_mtime;
      pFileSize = resourceInfoPtr->st_size;
      pPermissions = resourceInfoPtr->st_mode;
      pFullPath = pathname;
      delete resourceInfoPtr;
      return errorCode;
  }
  else
  {
      return errno;
  }
}

int FileInfo::getData(string path)
{
    ;
}

string FileInfo::FullPath()
{
    return string(pFullPath);
}

string FileInfo::DateModified()
{
    return string(pDateModified);
}

unsigned long FileInfo::FileSize()
{
    return pFileSize;
}

unsigned int FileInfo::Permissions()
{
    return pPermissions;
}

FileObject::FileObject()
{
    pContent="";
}

int FileObject::getData(string pathname)
{
    int errorCode = getStats(pathname);

    if(errorCode == 0)
    {
      //set permissions equal to values defined in stat.h documentation
      unsigned int permissions = (S_IRUSR | S_IROTH);

      //
      if((pPermissions & permissions) != permissions)
      {
          //Permission denied error
          errorCode= EACCES;
      }
      ifstream fin;
      fin.open(pathname.c_str());
      if(fin.is_open())
      {
          char *buffer = new char[pFileSize];
          fin.read(buffer, pFileSize);
          pContent = string(buffer,pFileSize);
          fin.close();
      }

      return errorCode;
    }
}

string FileObject::Content()
{
    return pContent;
}
