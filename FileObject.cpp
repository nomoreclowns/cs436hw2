#include <iostream>
#include <string>
#include <cerrno>
#include <fstream>
using namespace std;
#include <sys/stat.h>
#include <unistd.h>
#include "FileObject.h"

FileInfo::FileInfo()
{
    pFullPath="";
    pDateModified=0;
}

int FileInfo::getStats(string pathname)
{
  FileStats *resourceInfoPtr = new FileStats();

  errno=0;
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
    return getStats(path);
}

int FileInfo::DeleteFile(string pathname)
{

    errno=0;
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
      errno=0;
      remove(pathname.c_str());
      errorCode = errno;
    }

    return errorCode;
}

/*
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
*/

FileReader::FileReader()
{
    pContent="";
}

int FileReader::getData(string pathname)
{
    errno=0;
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
      if(fin.is_open() == false)
      {
          return -1;
      }

      char *buffer = new char[pFileSize];
      fin.read(buffer, pFileSize);
      pContent = string(buffer,pFileSize);
      fin.close();

      return errorCode;
    }
    else
    {
        return errno;
    }
}

/*
string FileObject::Content()
{
    return pContent;
}
*/


FileWriter::FileWriter(string fileContent)
{
    Content=fileContent;
}

int FileWriter::Write(string filePath)
{

    FileStats *resourceInfoPtr = new FileStats();

    errno=0;
    access(filePath.c_str(), W_OK);
    int errorCode = errno;

    if(errorCode == ENOENT)
    {
        ofstream output;
        output.open(filePath.c_str(), ios::out);
        if(output.is_open() == true)
        {
            output.write(Content.c_str(), Content.size());
            output.close();
            return 0;
        }
        else
        {
            return EACCES;
        }
    }
    return errorCode;
}






