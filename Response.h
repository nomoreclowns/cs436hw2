#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>
using namespace std;

#include "Utilities.h"

class Response {
 public:
  HttpVersion Version;
  short status;
  string entity;
  virtual void Form();
  Response();
};

class GetHeadResponse
{
public:
  int dateModified;
  unsigned long Size;
  virtual void Form();
};

class PutPostResponse
{
public:
  unsigned long Size;
  virtual void Form();
};

class DeleteResponse
{
public:
  virtual void Form();
};

#endif // SERVER_H
