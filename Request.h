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

#endif // REQUEST_H
