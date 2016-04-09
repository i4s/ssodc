#include "utils/Daemon.hpp"

int main()
{
    ssodc::utils::daemon map;
    map.daemonize();
    return 0;
}