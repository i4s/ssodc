#ifndef SSODC_DIVIDER_DIVIDER_H_
#define SSODC_DIVIDER_DIVIDER_H_

#include "daemon.h"

class Divider : public Daemon
{
 public:
  Divider();
  ~Divider();

  int Daemonize();
};

#endif //SSODC_DIVIDER_DIVIDER_H_