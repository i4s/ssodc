#include "Divider.h"

Divider::Divider() : Daemon("/",1) 
{

}

int Divider::Daemonize()
{
	Daemonize();
	while(true)
	{
		//wait new tasks
		sleep(delay);
	}
	return 0;
}