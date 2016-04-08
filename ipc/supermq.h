#ifndef SSODC_DIVIDER_SUPERMQ_H_
#define SSODC_DIVIDER_SUPERMQ_H_

#include "socketconnection.h"

class SuperMQ : private SocketConnection
{
public:
    SuperMQ();
    SuperMQ(int);
    SuperMQ(std::string, int);
    virtual ~SuperMQ();

    int Connect(const std::string&, int);
    int Receive(int, std::string&);
    int Receive(std::string&);
    int Send(std::string&) const;
    void Accept(SuperMQ&);
};

#endif //SUPERMQ