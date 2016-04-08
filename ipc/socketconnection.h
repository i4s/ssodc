#ifndef SSODC_DIVIDER_SOCKETCONNECTION_H_
#define SSODC_DIVIDER_SOCKETCONNECTION_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <string>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

const int kMaxConnections = 5;
const int kMaxHostName = 200;
const int kMaxRecv = 500;

class SocketConnection {
private:
    int sock;
    struct sockaddr_in socket_address;
public:
    SocketConnection();
    virtual ~SocketConnection();

    int Connect(const std::string, const int port);
    int Create();
    int Bind(const int port);
    int Listen() const;
    int Accept(SocketConnection&) const;
    int Send(const std::string) const;
    int Recv(std::string&) const;
    void SetNonBlocking(const bool);
    bool is_valid() const;
};

#endif //SSODC_DIVIDER_SOCKETCONNECTION_H_