#ifndef SERVER_H
#define SERVER_H

#include <string>
using namespace std;
#include "Request.h"
#include "Response.h"
#include "Utilities.h"
#include "FileObject.h"

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

    friend void* ThreadFunction(void* serverArgument)
    {
        return ((ThreadPackage*)(serverArgument))->ServerInstance->PthreadWorkFunction((ThreadPackage*)serverArgument);
    }

    const static unsigned short defaultPort=80;
    const static unsigned int PayloadSize=255;
    const static unsigned int requestSize=100;
    unsigned short portNumber;
    //void* packageToThread;

    Server(unsigned short);

    static void *PthreadWorkFunction_obsolete(void*);

    void *PthreadWorkFunction(ThreadPackage*);

    static char *DNSLookupFunction(char [], int );

    Response ProcessCommand(string);

    void tryGET(Request );

    void tryPUT(Request );

    void tryHEAD(Request );

    void tryDELETE(Request );

    // The GetFile function returns an object of type Response
    // pathname holds the file location of the file being requested
    // clientCommand holds the command the client is executing.
    Response GetFile(string pathname, Command clientCommand);

public:

    static Server GenerateServer(string);
    static Server GenerateServer();

    int Run();

};

#endif // SERVER_H
