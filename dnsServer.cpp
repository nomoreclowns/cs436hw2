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
#include "Server.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    Server* someServer;
    //check the number of arguments
    if(argc != 2)
    {
        someServer = Server::GenerateServer();
    }
    else
    {
        someServer= Server::GenerateServer(argv[1]);
    }


    someServer->Run();

	return 0;
}
