#include "supermq.h"
#include <stdio.h>

SuperMQ::SuperMQ() : SocketConnection::SocketConnection()
{
}

SuperMQ::SuperMQ(int port) : SocketConnection::SocketConnection()
{
    if(SocketConnection::Create() == -1)
    {
        //TODO ERROR
    }
    if(SocketConnection::Bind(port) == -1)
    {
        //TODO ERROR
    }
    if(SocketConnection::Listen() == -1)
    {
        //TODO ERROR
    }
}

SuperMQ::SuperMQ(std::string host, int port) : SocketConnection::SocketConnection()
{
    if(SocketConnection::Create() == -1)
    {
        //TODO ERROR
    }
    if(SocketConnection::Connect(host, port) == -1)
    {
        //TODO ERROR
    }
}

SuperMQ::~SuperMQ()
{
}

int SuperMQ::Connect(const std::string& host, int port)
{
    if(SocketConnection::Create() == -1)
    {
        //TODO ERROR
    }
    if(SocketConnection::Connect(host, port) == -1)
    {
        //TODO ERROR
        return -1;
    }
    return 0;
}

int SuperMQ::Receive(int port, std::string& data)
{
    if(SocketConnection::Create() == -1)
    {
        //TODO ERROR
    }
    if(SocketConnection::Bind(port) == -1)
    {
        //TODO ERROR
    }
    if(SocketConnection::Listen() == -1)
    {
        //TODO ERROR
    }
    SuperMQ client;
    Accept(client);
    if(client.Recv(data) == -1)
    {
        //TODO ERROR
        return -1;
    }
    return 0;
}

int SuperMQ::Receive(std::string& data)
{
    SuperMQ client;
    Accept(client);
    if(client.Recv(data) == -1)
    {
        //TODO ERROR
        return -1;
    }
    return 0;
}

void SuperMQ::Accept(SuperMQ& smq)
{
    if(SocketConnection::Accept(smq) == -1)
    {
        //TODO ERROR
    }
}

int SuperMQ::Send(std::string& data) const
{
    if(SocketConnection::Send(data) == -1)
    {
        //TODO ERROR
        return -1;
    }
    return 0;
}