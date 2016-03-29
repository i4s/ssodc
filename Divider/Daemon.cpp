#include "Daemon.h"

Daemon::Daemon(string dr, int dl)
{
    dir = dr;
    delay = dl;
}

int Daemon::Daemonize()
{
    pid_t pid, sid;
    pid = fork();
    if(pid < 0)
    {
        exit(EXIT_FAILURE);
    }
    else if(pid > 0)
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
    	umask(0);
    	sid = setsid();
    	if (sid < 0)
    	{ 
    	    exit(EXIT_FAILURE); 
    	}
    	if ((chdir(dir.c_str())) < 0) 
    	{ 
    	    exit(EXIT_FAILURE);
    	}
    	close(STDIN_FILENO);
    	close(STDOUT_FILENO);
    	close(STDERR_FILENO);
    }
    return 0;
}