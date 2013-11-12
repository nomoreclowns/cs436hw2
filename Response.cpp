#include <string>
using namespace std;
#include "Response.h"

Response::Response()
{
  status = 0;
  dateModified = 0;
  contents = "";
}

void Response::printReponse()
{
    string package="";
    package.reserve(5);
}
