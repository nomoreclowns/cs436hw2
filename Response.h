#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

class Response {
 public:
  short status;
  string metadata;
  string contents;
  void printReponse();
};

#endif // SERVER_H
