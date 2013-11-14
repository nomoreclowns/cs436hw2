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
//#include <errno.h>

//Project headers
#include "Response.h"
#include "Server.h"
#include "Utilities.h"
#include "HttpHandler.h"

//private constructor for class used by the factory method
Server::Server(unsigned short inPortNumber)
{
    portNumber = inPortNumber;
}

//static factory method for creating server objects
Server* Server::GenerateServer()
{
    Server* package= new Server(defaultPort);

    return package;
}

Server* Server::GenerateServer(string inPortNumber)
{
    int port;
    try
    {
        port = stoi(inPortNumber);
    }
    catch(...)
    {
        port=defaultPort;
    }
    Server* package= new Server(port);

    return package;
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
		pthread_create(&tid[threadIndex], nullptr, &ThreadFunction, packageToThread);

		threadIndex++;
	}

    //don't know yet if this works properly
	for(int someIndex=0; someIndex <= threadIndex; someIndex++)
	{
		pthread_join(tid[someIndex],nullptr);
	}

	return 0;
}

void* Server::PthreadWorkFunction(ThreadPackage* packageToThread)
{
    if (packageToThread == nullptr)
    {
        return packageToThread;
    }

    int socketID= packageToThread->SocketData;
    HttpHandler Service;

	char clientRequest[requestSize];
	Utilities::initializeBuffer(clientRequest, requestSize, 0);
	cout<<"waiting for client request..."<<endl;
	recv(socketID, clientRequest, requestSize, 0);
	cout<<"received request!"<<endl;

	string unprocessedRequest= string(clientRequest, requestSize);
	cout<<unprocessedRequest<<endl;
	string processedRequest= Service.ProcessCommand(unprocessedRequest);
	cout<<processedRequest<<endl;
	send(socketID, processedRequest.c_str(), processedRequest.size(), 0);

	return nullptr;
}

Response Server::GetFile(string pathname, Command clientCommand)
{
  Response myResponse;
  //struct stat myStat;
  FileStats *fileMetaData = new FileStats();
  int functionError =  stat(pathname.c_str(), fileMetaData);

  if(functionError == 0)
  {
      //set permissions equal to values defined in stat.h documentation
      unsigned int permissions = (S_IRUSR | S_IROTH);

      //
      if((fileMetaData->st_mode & permissions) != permissions)
      {
          //Permission denied error
          //myResponse.status = ;
      }
      myResponse.status = 200;
      //myResponse.dateModified = fileMetaData->st_mtime;

      ifstream fin;
      if(clientCommand == GET)
      {
            fin.open(pathname.c_str());
            if(fin.is_open())
            {
              char *buffer = new char[fileMetaData->st_size];
              fin.read(buffer,fileMetaData->st_size);
              myResponse.entity = string(buffer,fileMetaData->st_size);
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
      else
      {
          //Unspecified error
          //myResponse.status = ;
      }
  }



  return myResponse;
}
