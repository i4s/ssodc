#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

using namespace std;

class Daemon 
{
protected:
	string dir;
	int delay;
public:
	Daemon(string, int);
	virtual int Daemonize();
};