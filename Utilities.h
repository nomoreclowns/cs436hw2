#ifndef UTILITIES_H
#define UTILITIES_H


class Server;

enum Command
{
    GET=1,
    HEAD=2,
    POST=4,
    PUT=8,
    DELETE=16,
    GARBAGE=32
};

enum HttpVersion
{
    OneZero=0,
    OneOne=1,
    ZeroNine=2
};

class Utilities
{
    public:
        Utilities();
        static void initializeBuffer(char*, int, int);
    private:
};

class ThreadPackage
{
public:
    ThreadPackage();
    ThreadPackage(Server*, int);

    Server* ServerInstance;
    int SocketData;
};

#endif // UTILITIES_H
