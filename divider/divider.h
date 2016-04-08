#ifndef SSODC_DIVIDER_DIVIDER_H_
#define SSODC_DIVIDER_DIVIDER_H_

#include "../utils/daemon.h"
#include "../ipc/supermq.h"
#include <string>

class Divider : public Daemon
{
public:
    Divider();
    ~Divider();

    int Daemonize();
};

#endif //SSODC_DIVIDER_DIVIDER_H_