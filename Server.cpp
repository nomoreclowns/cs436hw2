//C++ headers
#include <iostream>
#include <cerrno>
#include <string>
// the following was included to open a file in the GetFile function
#include <fstream>
using namespace std;

//C headers
#include <pthread.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <errno.h>

//Project headers
#include "Response.h"
#include "Server.h"
#include "Utilities.h"

//private constructor for class used by the factory method
Server::Server(unsigned short inPortNumber)
{
    portNumber=inPortNumber;
}

//static factory method for creating server objects
Server Server::GenerateServer(unsigned short port)
{
    Server* package= new Server(port);

    return *package;
}

//start the server... simple enough
int Server::Run()
{
    //use the socket system call to get an ID for a socket
	int initialSocketDesc = socket(PF_INET, SOCK_STREAM, 0);

    // struct to hold the information about the server
	struct sockaddr_in *serverAddr=new struct sockaddr_in();
	serverAddr->sin_family=AF_INET;
	serverAddr->sin_port=htons(portNumber);
	serverAddr->sin_addr.s_addr= INADDR_ANY;

    //using the bind system call
	int returnStatus=bind(initialSocketDesc, (struct sockaddr *) serverAddr, sizeof(*serverAddr));
	if(returnStatus != 0)
	{
		return returnStatus;
	}

	//using the listen system cal/
	listen(initialSocketDesc, 5);
	cout<<"listening ..."<<endl;

    // crating a struct to hold client information
	struct sockaddr_in clientAddr;
	socklen_t clientLength = sizeof(clientAddr);

    // initialize an array to hold thread ID's
	pthread_t tid[50];
	int threadIndex=0;
	ThreadPackage* packageToThread;

	while(true)
	{
	  cout<<"waiting to accept..."<<endl;
	  // this system call is blocking, and it generates a new socket to communicate with the client
	  // so the old one can continue to be used for clients trying to connect
		int newSocketDesc=accept(initialSocketDesc, (struct sockaddr *) &clientAddr, &clientLength);

		cout<<"accepted connection"<<endl;
		//set the pointer to point to the ID of the new socket that will be used to communicate with connected client
		packageToThread=new ThreadPackage(this, newSocketDesc);

		//create a new thread and give it a pointer to the function that handles clients
		pthread_create(&tid[threadIndex], 0, &ThreadFunction, packageToThread);

		threadIndex++;
	}

    //don't know yet if this works properly
	for(int someIndex=0; someIndex <= threadIndex; someIndex++)
	{
		pthread_join(tid[someIndex],NULL);
	}

	return 0;
}

Response Server::ProcessCommand(string command)
{
    Response* ServerResponse = new Response();

    Request* ClientRequest= new Request();
    ClientRequest->Parse(command);
    switch(ClientRequest->CommandRequest)
    {
    case GET:
        ;
        break;
    case PUT:
        ;
        break;
    case HEAD:
        ;
        break;
    case DELETE:
        ;
        break;
    default:
        break;

    }

    return *ServerResponse;
}

void Server::tryGET(Request clientRequest)
{
    GetFile(clientRequest.Path, clientRequest.CommandRequest);
}

void Server::tryPUT(Request clientRequest)
{

}

void Server::tryHEAD(Request clientRequest)
{

}

void Server::tryDELETE(Request clientRequest)
{

}

void* Server::PthreadWorkFunction_obsolete(void* packageToThread1)
{
    if (packageToThread1 == NULL)
    {
        return packageToThread1;
    }

    int *socketID= (int*)packageToThread1;

	char clientRequest[requestSize];
	//char *clientRequestPtr=clientRequest;
	cout<<"waiting for client request..."<<endl;
	recv(*socketID, clientRequest, requestSize, 0);
	cout<<"received request!"<<endl;
	//char *DNSResponse=DNSLookupFunction(clientRequest, requestSize);
	//cout<<"DNSResponse = "<<DNSResponse<<endl;
	//send(*socketID, DNSResponse, PayloadSize, 0);

	return (void*)0;
}

void* Server::PthreadWorkFunction(ThreadPackage* packageToThread)
{
    if (packageToThread == NULL)
    {
        return packageToThread;
    }

    int socketID= packageToThread->SocketData;

	char clientRequest[requestSize];
	//char *clientRequestPtr=clientRequest;
	cout<<"waiting for client request..."<<endl;
	recv(socketID, clientRequest, requestSize, 0);
	cout<<"received request!"<<endl;
	//char *DNSResponse=DNSLookupFunction(clientRequest, requestSize);
	//cout<<"DNSResponse = "<<DNSResponse<<endl;
	//send(socketID, DNSResponse, PayloadSize, 0);

	return (void*)0;
}

Response Server::GetFile(string pathname, Command clientCommand)
{
  Response myResponse;
  struct stat myStat;
  struct stat *myStatPointer = &myStat;
  int functionError =  stat(pathname.c_str(), myStatPointer);

  if(functionError == 0)
  {
      myResponse.status = 200;
      myResponse.dateModified = myStat.st_mtime;

      ifstream fin;
      if(clientCommand == GET)
      {
            fin.open(pathname.c_str());
            if(fin.is_open())
            {
              char *buffer = new char[myStat.st_size];
              fin.read(buffer,myStat.st_size);
              myResponse.contents = string(buffer,myStat.st_size);
              fin.close();
            }
      }
  }
  else
  {
      int errorValue = errno;
      if(errorValue == EACCES)
      {
          //Permission denied error
          //myResponse.status = ;
      }
      else if(errorValue == ENOENT)
      {
          myResponse.status = 404;
      }
  }



  return myResponse;
}
