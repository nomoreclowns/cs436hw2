#ifndef SERVER_H
#define SERVER_H


#include <string>
using namespace std;
#include "Request.h"

typedef struct
{
  string Name;
  string ipAddresses;
  int byteCount;
} response;

void* ThreadFunction(void*);

class Server
{
private:

    const static unsigned int PayloadSize=255;
    const static unsigned int requestSize=100;
    unsigned short portNumber;
    void* packageToThread;

    Server(unsigned short);

    static void *PthreadWorkFunction(void*);

    static char *DNSLookupFunction(char [], int );

    static Request ParseCommand(string);


public:

    static Server GenerateServer(unsigned short);

    int Run();


};

#endif // SERVER_H
