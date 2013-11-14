//C++ headers
#include <iostream>
#include <cerrno>
#include <string>
using namespace std;

//Project headers
#include "FileObject.h"
#include "HttpHandler.h"


string HttpHandler::ProcessCommand(string command)
{
    string ServerResponse="";

    Request ClientRequest;//= new Request();
    ClientRequest.Parse(command);
    /*
    switch(ClientRequest.CommandRequest)
    {
    case GET:
        GetHeadResponse Data = tryGET(ClientRequest);
        break;
    case HEAD:
        //GetHeadResponse Data = tryHEAD(ClientRequest);
        break;
    case PUT:
        ;
        break;
    case POST:
        ;
        break;
    case DELETE:
        DeleteResponse Data = tryDELETE(ClientRequest);
        break;
    default:
        break;
    }
    */
    auto var=ClientRequest.CommandRequest;
    if(ClientRequest.CommandRequest==GET)
    {
        GetHeadResponse Data = tryGET(ClientRequest);
        ServerResponse = Data.Form();
    }
    else if(ClientRequest.CommandRequest==HEAD)
    {
        GetHeadResponse Data = tryHEAD(ClientRequest);
        ServerResponse= Data.Form();
    }
    else if(ClientRequest.CommandRequest==PUT)
    {
        PutPostResponse PData = tryPUT(ClientRequest);
        ServerResponse= PData.Form();
    }
    else if(ClientRequest.CommandRequest==DELETE)
    {
        DeleteResponse DData = tryDELETE(ClientRequest);
        ServerResponse= DData.Form();
    }

    return ServerResponse;
}

GetHeadResponse HttpHandler::tryGET(Request clientRequest)
{
    GetHeadResponse ServerResponse;
    ServerResponse.Version= OneZero;
    FileReader RequestedFile;
    int errorCode= RequestedFile.getData(clientRequest.Path);
    if(errorCode==0)
    {
        ServerResponse.dateModified= RequestedFile.DateModified();
        ServerResponse.entity= RequestedFile.Content();
        ServerResponse.Size= RequestedFile.FileSize();
        ServerResponse.status= 200;
    }
    else if(errorCode == EACCES)
    {
        ServerResponse.status= 403;
    }
    else if(errorCode == ENOENT)
    {
        ServerResponse.status= 404;
    }

    return ServerResponse;
}

PutPostResponse HttpHandler::tryPUT(Request clientRequest)
{
    PutPostResponse ServerResponse;
    ServerResponse.Version= OneZero;
    FileWriter someFile(clientRequest.body);
    int errorCode=someFile.Write(clientRequest.Path);
    if(errorCode==0)
    {
        ServerResponse.status= 200;
    }
    else if(errorCode == EACCES)
    {
        ServerResponse.status= 403;
    }
    else if(errorCode == ENOENT)
    {
        ServerResponse.status= 404;
    }

    return ServerResponse;
}

GetHeadResponse HttpHandler::tryHEAD(Request clientRequest)
{
    GetHeadResponse ServerResponse;
    ServerResponse.Version= OneZero;
    FileInfo RequestedFile;
    int errorCode= RequestedFile.getData(clientRequest.Path);
    if(errorCode==0)
    {
        ServerResponse.dateModified= RequestedFile.DateModified();
        ServerResponse.Size= RequestedFile.FileSize();
        ServerResponse.status= 200;
    }
    else if(errorCode == EACCES)
    {
        ServerResponse.status= 403;
    }
    else if(errorCode == ENOENT)
    {
        ServerResponse.status= 404;
    }

    return ServerResponse;
}

DeleteResponse HttpHandler::tryDELETE(Request clientRequest)
{
    DeleteResponse ServerResponse;
    ServerResponse.Version= OneZero;
    FileInfo RequestedFile;
    int errorCode= RequestedFile.DeleteFile(clientRequest.Path);
    if(errorCode==0)
    {
        //ServerResponse.dateModified= RequestedFile.DateModified();
        //ServerResponse.Size= RequestedFile.FileSize();
        ServerResponse.status= 200;
    }
    else if(errorCode == EACCES)
    {
        ServerResponse.status= 403;
    }
    else if(errorCode == ENOENT)
    {
        ServerResponse.status= 404;
    }

    return ServerResponse;
}
