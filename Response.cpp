#include <string>
using namespace std;
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
            package="HTTP/1.0 200\r\nContent-Length:"+to_string(Size)+"\r\nLast-Modified:xxxxxx\r\n";
        }
        else
        {
            package="HTTP/1.0 200\r\nContent-Length:"+to_string(Size)+"\r\nLast-Modified:xxxxxx\r\n"+entity;
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
    package.reserve(5);

    return package;
}

string DeleteResponse::Form()
{
    string package="";
    package.reserve(5);

    return package;
}
