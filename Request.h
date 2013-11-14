#ifndef REQUEST_H
#define REQUEST_H

#include <string>
using namespace std;

#include "Utilities.h"

class Request
{
    public:
        void Parse(string);

        Request();
        Request(string);

        Command CommandRequest;
        string Path;
        HttpVersion Version;
        string headers[];
        string body;
    private:
        Command ParseCommand(string&);
        string ParsePath(string&);
        HttpVersion ParseHTTPVersion(string&);
};


#endif // REQUEST_H
