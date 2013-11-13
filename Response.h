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
  virtual string Form();
  Response();
};

class GetHeadResponse : public Response
{
public:
  int dateModified;
  unsigned long Size;
  virtual string Form();
};

class PutPostResponse : public Response
{
public:
  unsigned long Size;
  virtual string Form();
};

class DeleteResponse : public Response
{
public:
  virtual string Form();
};

#endif // SERVER_H
