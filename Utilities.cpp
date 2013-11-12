#include "Utilities.h"

Utilities::Utilities()
{
    //ctor
}

void Utilities::initializeBuffer(char buffer[], int size, int initialValue)
{
    for (int i=0; i<size; i++)
    {
        buffer[i]= initialValue;
    }
}



ThreadPackage::ThreadPackage()
{
    ServerInstance=nullptr;
    SocketData=0;
}

ThreadPackage::ThreadPackage(Server* ptr, int someInt)
{
    ServerInstance=ptr;
    SocketData=someInt;
}
