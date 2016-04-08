#include "divider.h"

Divider::Divider() : Daemon()
{
}

Divider::~Divider()
{
}

int Divider::Daemonize()
{
    Daemon::Daemonize();
    while(!terminate)
    {
        SuperMQ smq;
        std::string message;
        smq.Receive(6900, message);
    }
    return 0;
}