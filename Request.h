#ifndef REQUEST_H
#define REQUEST_H

#include <string>
using namespace std;

class Request
{
    public:
        Request();
        string Command;
        string Path;
        string Version;
};

enum Command
{
    GET=1,
    HEAD=2,
    POST=4,
    DELETE=8,
    GARBAGE=16
};

#endif // REQUEST_H
