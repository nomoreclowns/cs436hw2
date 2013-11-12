//C++ headers
#include <iostream>
#include <cerrno>
#include <string>
using namespace std;

//Project headers
#include "HttpHandler.h"


string HttpHandler::ProcessCommand(string command)
{
    string ServerResponse;

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
    case POST:
        ;
        break;
    case DELETE:
        ;
        break;
    default:
        break;

    }

    return ServerResponse;
}

void HttpHandler::tryGET(Request clientRequest)
{
    ;
}

void HttpHandler::tryPUT(Request clientRequest)
{

}

void HttpHandler::tryHEAD(Request clientRequest)
{

}

void HttpHandler::tryDELETE(Request clientRequest)
{

}
