#ifndef SERVER_H
#define SERVER_H


#include <string>
using namespace std;


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
    //int initialSocketDesc;
    void* packageToThread;

    Server(unsigned short);
/*
    friend void* ThreadFunction(void* arg)
    {
        return ((Server*)arg)->PthreadWorkFunction();
    }
*/

    static void *PthreadWorkFunction(void*);

    static char *DNSLookupFunction(char [], int );

public:

    static Server GenerateServer(unsigned short);

    int Run();


};

#endif // SERVER_H
