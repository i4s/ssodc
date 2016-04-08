#ifndef SSODC_DIVIDER_DAEMON_H_
#define SSODC_DIVIDER_DAEMON_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

class Daemon
{
protected:
    static bool terminate;
public:
    Daemon();
    ~Daemon();

    virtual int Daemonize();
private:
    static void TerminateHandler(int);
};

#endif //SSODC_DIVIDER_DAEMON_H_