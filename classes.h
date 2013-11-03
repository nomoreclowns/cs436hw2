#ifndef CLASSES_H
#define CLASSES_H

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

    const static int PayloadSize=255;
    const static int requestSize=100;
    unsigned short portNumber;
    //int initialSocketDesc;
    void* packageToThread;

    Server(unsigned short);

    friend void* ThreadFunction(void* arg)
    {
        return ((Server*)arg)->PthreadWorkFunction();
    }


public:

    static Server GenerateServer(unsigned short);

    int Run();

    void *PthreadWorkFunction();

    char *DNSLookupFunction(char [], int );

};


#endif
