#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

using namespace std;

class Response {
 public:
  short status;
  int dateModified;
  string contents;
  void printReponse();
  Response();
};



#endif // SERVER_H
