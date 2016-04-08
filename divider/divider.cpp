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
        smq.Listen(6900, message);
        break;
    }
    return 0;
}