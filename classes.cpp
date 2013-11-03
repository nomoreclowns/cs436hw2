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
#include "classes.h"

#define REQUESTSIZE 100
#define PAYLOADSIZE 255

Server::Server(unsigned short inPortNumber)
{
    portNumber=inPortNumber;

    packageToThread= NULL;
}

Server Server::GenerateServer(unsigned short port)
{
    Server* package= new Server(port);

    return *package;
}

int Server::Run()
{
	int initialSocketDesc = socket(PF_INET, SOCK_STREAM, 0);

	struct sockaddr_in *serverAddr=new struct sockaddr_in();
	serverAddr->sin_family=AF_INET;
	serverAddr->sin_port=htons(portNumber);
	serverAddr->sin_addr.s_addr= INADDR_ANY;

	int returnStatus=bind(initialSocketDesc, (struct sockaddr *) serverAddr, sizeof(*serverAddr));
	if(returnStatus != 0)
	{
		return returnStatus;
	}
	cout<<"about to listen"<<endl;
	listen(initialSocketDesc, 5);
	cout<<"listening ..."<<endl;
	struct sockaddr_in clientAddr;
	socklen_t clientLength = sizeof(clientAddr);

	pthread_t tid[50];
	int threadIndex=0;

	while(true)
	{
	  cout<<"waiting to accept..."<<endl;
		int newSocketDesc=accept(initialSocketDesc, (struct sockaddr *) &clientAddr, &clientLength);

		cout<<"accepted connection"<<endl;
		packageToThread=&newSocketDesc;
		pthread_create(&tid[threadIndex], 0, ThreadFunction, (void*)this);

		threadIndex++;
	}

	for(int someIndex=0; someIndex <= threadIndex; someIndex++)
	{
		pthread_join(tid[someIndex],NULL);
	}

	return 0;
}




char* Server::DNSLookupFunction(char requestedDns[], int size)
{
	cout<<"In Function DNSLookupFunction()"<<endl;

	unsigned int count;
	struct hostent *dnsInfoPtr;
	struct in_addr **addressList;
	string dnsString(requestedDns, size);

	string addressString= "";
	char payload[PAYLOADSIZE];
	for (count=0;count<PAYLOADSIZE;count++)
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

	for(count=count; count <PAYLOADSIZE; count++)
	{
		payload[count]='\0';
	}
	string temp(payload, PAYLOADSIZE);
	cout<<temp<<endl;

	return payload;

}

void* Server::PthreadWorkFunction()
{
    //Server* ServerObject = (Server*)integerSocketDescriptor;

    if (packageToThread == NULL)
    {
        return (void*)1;
    }
    int *socketID= (int*)packageToThread;

	char clientRequest[REQUESTSIZE];
	//char *clientRequestPtr=clientRequest;
	cout<<"waiting for client request..."<<endl;
	recv(*socketID, clientRequest, REQUESTSIZE, 0);
	cout<<"received request!"<<endl;
	char *DNSResponse=DNSLookupFunction(clientRequest, REQUESTSIZE);
	//cout<<"DNSResponse = "<<DNSResponse<<endl;
	send(*socketID, DNSResponse, PAYLOADSIZE, 0);

	return (void*)0;
}

