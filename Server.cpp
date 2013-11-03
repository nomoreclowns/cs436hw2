#include <iostream>
#include <cerrno>
#include <string>
using namespace std;
#include <pthread.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Server.h"

//#define requestSize 100
//#define PayloadSize 255

//private constructor for class used by the factory method
Server::Server(unsigned short inPortNumber)
{

    portNumber=inPortNumber;

    // this is initialized to NULL to access to random locations
    packageToThread= NULL;
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

	while(true)
	{
	  cout<<"waiting to accept..."<<endl;
	  // this system call is blocking, and it generates a new socket to communicate with the client
	  // so the old one can continue to be used for clients trying to connect
		int newSocketDesc=accept(initialSocketDesc, (struct sockaddr *) &clientAddr, &clientLength);

		cout<<"accepted connection"<<endl;
		//set the pointer to point to the ID of the new socket that will be used to communicate with connected client
		packageToThread=&newSocketDesc;

		//create a new thread and give it a pointer to the function that handles clients
		pthread_create(&tid[threadIndex], 0, Server::PthreadWorkFunction, packageToThread);

		threadIndex++;
	}

    //don't know yet if this works properly
	for(int someIndex=0; someIndex <= threadIndex; someIndex++)
	{
		pthread_join(tid[someIndex],NULL);
	}

	return 0;
}



//static function that does the DNS lookup
char* Server::DNSLookupFunction(char requestedDns[], int size)
{
	//cout<<"In Function DNSLookupFunction()"<<endl;

	unsigned int count;
	struct hostent *dnsInfoPtr;
	struct in_addr **addressList;

	//create a string out of the character array to hold the website name
	string dnsString(requestedDns, size);

	string addressString= "";

	//byte array to hold the DNS data
	char payload[PayloadSize];

    //initialize array to 0's just to be safe
	for (count=0;count<PayloadSize;count++)
	{
		payload[count]=0;
	}

	//this is a candidate for elimination
	if ((dnsInfoPtr = gethostbyname(dnsString.c_str())) == NULL) //get the host info
	{
		herror("gethostbyname");
		return payload;
	}

	addressString=dnsInfoPtr->h_name;
	addressString=addressString+"\n";

	addressList = (struct in_addr **)dnsInfoPtr->h_addr_list;
	for(count=0;addressList[count]!=NULL;count++)
	{
		addressString = addressString + inet_ntoa(*addressList[count]);
		addressString = addressString + "\n";
	}

	for(count=0;count < addressString.size(); count++)
	{
		payload[count]=addressString[count];
	}

	for(count=count; count <PayloadSize; count++)
	{
		payload[count]='\0';
	}
	string temp(payload, PayloadSize);
	cout<<temp<<endl;

	return payload;

}

void* Server::PthreadWorkFunction(void* packageToThread1)
{
    //Server* ServerObject = (Server*)integerSocketDescriptor;

    if (packageToThread1 == NULL)
    {
        return (void*)1;
    }
    int *socketID= (int*)packageToThread1;

	char clientRequest[requestSize];
	//char *clientRequestPtr=clientRequest;
	cout<<"waiting for client request..."<<endl;
	recv(*socketID, clientRequest, requestSize, 0);
	cout<<"received request!"<<endl;
	char *DNSResponse=DNSLookupFunction(clientRequest, requestSize);
	//cout<<"DNSResponse = "<<DNSResponse<<endl;
	send(*socketID, DNSResponse, PayloadSize, 0);

	return (void*)0;
}
