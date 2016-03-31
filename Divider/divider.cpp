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
    //wait tasks 
  }
  return 0;
}