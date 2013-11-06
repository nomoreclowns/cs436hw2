#ifndef SERVER_H
#define SERVER_H


#include <string>
using namespace std;
#include "Request.h"
#include "Response.h"

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

    static Command tryParseCommand(string command);

    static void tryGET(string command);

    static void tryPUT(string command);

    static void tryHEAD(string command);

    static void tryDELETE(string command);

    // The GetFile function returns an object of type Response
    // pathname holds the file location of the file being requested
    // clientCommand holds the command the client is executing.
    Response GetFile(string pathname, Command clientCommand);

public:

    static Server GenerateServer(unsigned short);

    int Run();


};

#endif // SERVER_H
