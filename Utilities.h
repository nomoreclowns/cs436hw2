#ifndef UTILITIES_H
#define UTILITIES_H


class Server;

class Utilities
{
    public:
        Utilities();
        static void initializeBuffer(char*, int, int);
    protected:
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
