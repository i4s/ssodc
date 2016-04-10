#ifndef SSODC_IPC_IPROCESSMQINTERFACE_HPP_
#define SSODC_IPC_IPROCESSMQINTERFACE_HPP_

#include <string>

namespace ssodc {
namespace ipc {

class IProcessMQInterface {
public:
    virtual int Connect(std::string, int) = 0;
    virtual int Bind(std::string) = 0;
    virtual int Send(std::string) = 0;
    virtual int Recv(std::string) = 0;
};
}
}

#endif //SSODC_IPC_IPROCESSMQINTERFACE_HPP_