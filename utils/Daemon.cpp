#include "Daemon.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <cstdlib>

namespace ssodc {
namespace utils {

bool Daemon::m_terminate;

Daemon::Daemon() {
    struct sigaction terminateAction;
    sigset_t terminateSet;
    terminateAction.sa_flags = 0;
    sigemptyset(&terminateAction.sa_mask);
    sigfillset(&terminateSet);
    sigdelset(&terminateSet, SIGTERM);
    sigprocmask(SIG_SETMASK, &terminateSet, 0);
    terminateAction.sa_handler = &TerminateHandler;
    sigaction(SIGTERM, &terminateAction, 0);
    pid_t pid = fork();
    // TODO: Change this stuff, when exception model will be implemented
    exit(pid > 0 ? EXIT_SUCCESS : EXIT_FAILURE);
    setsid();
    chdir("/");
    umask(0);
    // TODO: Change this stuff, when exception model will be implemented
    pid = fork();
    exit(pid > 0 ? EXIT_SUCCESS : EXIT_FAILURE);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

Daemon::~Daemon() {
}

void Daemon::TerminateHandler(int i) {
    m_terminate = true;
}

int Daemon::Start() {
    Run();
    return 0;
}

}
}