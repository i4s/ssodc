#include "daemon.h"

bool Daemon::terminate = false;

Daemon::Daemon()
{
  struct sigaction terminate_action;
  sigset_t terminate_set;
  terminate_action.sa_flags = 0;
  sigemptyset(&terminate_set);
  sigemptyset(&terminate_action.sa_mask);
  sigaddset(&terminate_set, SIGHUP);
  sigprocmask(SIG_BLOCK, &terminate_set, 0);
  terminate_action.sa_handler = &TerminateHandler;
  sigaction(SIGTERM, &terminate_action, 0);
}

Daemon::~Daemon()
{
}

void Daemon::TerminateHandler(int i)
{
  terminate = true;
}

int Daemon::Daemonize()
{
  if(pid_t pid = fork())
  {
    if(pid < 0)
    {
      exit(EXIT_FAILURE);
    }
    else if(pid > 0)
    {
      exit(EXIT_SUCCESS);
    }
  }
  setsid();
  chdir("/");
  umask(0);
  if(pid_t pid = fork())
  {
    if(pid < 0)
    {
      exit(EXIT_FAILURE);
    }
    else if(pid > 0)
    {
      exit(EXIT_SUCCESS);
    }
  }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  return 0;
}