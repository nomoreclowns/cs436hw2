#include "Request.h"

Request::Request()
{
    //ctor
}

Request::Request(string command)
{
    Parse(command);
}

 void Request::Parse(string command)
{
    CommandRequest=ParseCommand(command);
    Path=ParsePath(command);
    Version=ParseHTTPVersion(command);
}

Command Request::ParseCommand(string clientCommand)
{
    unsigned int MinCommandSize=4;

    Command package= GARBAGE;

    if(clientCommand.length() > MinCommandSize)
    {
        string parsedCommand= clientCommand.substr(0, MinCommandSize);

        if(parsedCommand == "GET ")
        {
            package= GET;
        }
        else if(parsedCommand == "PUT ")
        {
            package= PUT;
        }
        else
        {
            MinCommandSize=5;
            parsedCommand.resize(MinCommandSize);
            parsedCommand= clientCommand.substr(0, MinCommandSize);
            if(parsedCommand == "HEAD ")
            {
                package= HEAD;
            }
            else if(parsedCommand == "POST ")
            {
                package= POST;
            }
            else
            {
            MinCommandSize=7;
            parsedCommand.resize(MinCommandSize);
                parsedCommand= clientCommand.substr(0, MinCommandSize);
                if (parsedCommand == "DELETE ")
                {
                    package= DELETE;
                }
                else
                {
                    return package;
                }
            }
        }
    }
    clientCommand.erase(0,MinCommandSize);
    return package;

}

string Request::ParsePath(string command)
{
	string path="";

	path.reserve(command.length());

	for (unsigned int i= 0; command[i] != ' ' && i< command.length(); i++)
	{
		path += command[i];
	}

	return path;
}

HttpVersion Request::ParseHTTPVersion(string command)
{
	//HTTP_1 Version = Zero;

	return OneZero;
}

