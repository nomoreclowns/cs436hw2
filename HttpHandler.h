#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H

#include <string>
using namespace std;

#include "Response.h"
#include "Request.h"

class HttpHandler
{
private:

    void tryGET(Request );

    void tryPUT(Request );

    void tryHEAD(Request );

    void tryDELETE(Request );

public:

    string ProcessCommand(string);
};



#endif
