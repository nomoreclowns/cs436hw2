#include <string>
using namespace std;
#include <ctime>
#include "Response.h"

Response::Response()
{
  status = 0;
  //dateModified = 0;
  entity = "";
}


string Response::Form()
{
    string package="";
    package.reserve(5);

    return package;
}

string GetHeadResponse::Form()
{
    string package="";
    package.reserve(50000);
    switch(status)
    {
    case 200:
        if(entity.size() <= 1)
        {
            package="HTTP/1.0 200\r\nContent-Length:"+to_string(Size)+"\r\nLast-Modified:"+ctime(&dateModified)+"\r\n";
        }
        else
        {
            package="HTTP/1.0 200\r\nContent-Length:"+to_string(Size)+"\r\nLast-Modified:"+ctime(&dateModified)+"\r\n"+entity+"\r\n";
        }

        break;
    case 403:
        package="HTTP/1.0 403\r\n";
        break;
    case 404:
        package="HTTP/1.0 404\r\n";
        break;
    }

    return package;
}

string PutPostResponse::Form()
{
    string package="";
    package.reserve(50000);
    switch(status)
    {
    case 200:
        package="HTTP/1.0 200\r\n\r\n";
        break;
    case 403:
        package="HTTP/1.0 403\r\n\r\n";
        break;
    case 404:
        package="HTTP/1.0 404\r\n\r\n";
    }

    return package;
}

string DeleteResponse::Form()
{
    string package="";
    package.reserve(50000);
    switch(status)
    {
    case 200:
        package="HTTP/1.0 200\r\n\r\n";
        break;
    case 403:
        package="HTTP/1.0 403\r\n\r\n";
        break;
    case 404:
        package="HTTP/1.0 404\r\n\r\n";
        break;
    }
    return package;
}
