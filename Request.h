#ifndef REQUEST_H
#define REQUEST_H

#include <string>
using namespace std;

enum Command
{
    GET=1,
    HEAD=2,
    POST=4,
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
        Request();
        enum Command CommandRequest;
        string Path;
        enum HTTP_1 Version;
};


#endif // REQUEST_H
