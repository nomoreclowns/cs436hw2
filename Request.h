#ifndef REQUEST_H
#define REQUEST_H

#include <string>
using namespace std;

enum Command
{
    GET=1,
    HEAD=2,
    PUT=4,
    DELETE=8,
    GARBAGE=16
};

enum HTTP_1
{
    Zero=0,
    One=1
};

class Request
{
    public:
        void Parse(string);

        Request();
        Request(string);

        Command CommandRequest;
        string Path;
        HTTP_1 Version;
    private:
        Command ParseCommand(string);
        string ParsePath(string);
        HTTP_1 ParseHTTPVersion(string);
};


#endif // REQUEST_H
