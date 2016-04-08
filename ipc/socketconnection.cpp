#include "socketconnection.h"

SocketConnection::SocketConnection() : sock(-1)
{
    memset(&socket_address, 0, sizeof(socket_address));
}

SocketConnection::~SocketConnection()
{
    if(is_valid())
    {
        close(sock);
    }
}

int SocketConnection::Create()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(!is_valid())
    {
        return -1;
    }
    int on = 1;
    return (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&on,
                       sizeof(on)) == -1) ? -1 : 0;
}

int SocketConnection::Bind(const int port)
{
    if(!is_valid())
    {
        return -1;
    }

    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = htons(INADDR_ANY);
    socket_address.sin_port = htons(port);
    return (bind(sock, (struct sockaddr*)&socket_address,
                 sizeof(socket_address)) == -1) ? -1 : 0;
}

int SocketConnection::Listen() const
{
    if(!is_valid())
    {
        return -1;
    }
    if(listen(sock, kMaxConnections) == -1)
    {
        return -1;
    }
    return 0;
}

int SocketConnection::Accept(SocketConnection& in_socket) const
{
    int address_lenght = sizeof(sock);
    in_socket.sock = accept(sock, (sockaddr*)&socket_address
                            , (socklen_t*)&address_lenght);
    if(in_socket.sock <= 0)
    {
        return -1;
    }
    return 0;
}

int SocketConnection::Send(const std::string str) const
{
    return (send(sock, str.c_str(), str.size(),
                 MSG_NOSIGNAL) == -1) ? -1 : 0;
}

int SocketConnection::Recv(std::string& str) const
{
    char buffer[kMaxRecv];
    str = "";
    memset(buffer, 0, kMaxRecv + 1);
    int status = recv(sock, buffer, kMaxRecv, 0);
    if(status == -1)
    {
        return -1;
    }
    else if(status == 0)
    {
        return 0;
    }
    else
    {
        str = buffer;
        return status;
    }
}

int SocketConnection::Connect(const std::string host, const int port)
{
    if(!is_valid())
    {
        return -1;
    }
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &socket_address.sin_addr);
    if(errno == EAFNOSUPPORT)
    {
        return -1;
    }
    return (connect(sock, (sockaddr*)&socket_address,
                    sizeof(socket_address)) == 0) ? 0 : -1;
}

void SocketConnection::SetNonBlocking(const bool b)
{
    int opts;
    opts = fcntl(sock, F_GETFL);
    if(opts < 0)
    {
        return;
    }
    if(b)
    {
        opts = (opts | O_NONBLOCK);
    }
    else
    {
        opts = (opts | ~O_NONBLOCK);
    }
    fcntl(sock, F_SETFL, opts);
}

bool SocketConnection::is_valid() const
{
    return (sock != -1);
}