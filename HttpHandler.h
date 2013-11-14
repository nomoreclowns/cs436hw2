#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H

#include <string>
using namespace std;

#include "Response.h"
#include "Request.h"

class HttpHandler
{
private:

    GetHeadResponse tryGET(Request );

    PutPostResponse tryPUT(Request );

    GetHeadResponse tryHEAD(Request );

    DeleteResponse tryDELETE(Request );

public:

    string ProcessCommand(string);
};



#endif
