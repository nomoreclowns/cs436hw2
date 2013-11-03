#include <pthread.h>
#include <iostream>
#include <cerrno>
#include <string>
using namespace std;
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "classes.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    unsigned short portNumber;
    //check the number of arguments
    if(argc != 2)
    {
        portNumber = 1025;
      //cout<<"Usage: "<<argv[0]<<" <port number>"<<endl;
      //return 1;
    }
    else
    {
        portNumber = atoi(argv[1]);
    }

    Server someServer= Server::GenerateServer(portNumber);

    someServer.Run();

	return 0;
}
