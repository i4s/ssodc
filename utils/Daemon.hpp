#ifndef SSODC_UTILS_DAEMON_HPP_
#define SSODC_UTILS_DAEMON_HPP_

namespace ssodc {
namespace utils {
class Daemon {
protected:
    static bool m_terminate;
public:
    Daemon();
    ~Daemon();
    virtual int Run() = 0;
    int Start();
private:
    static void TerminateHandler(int);
};
}
}

#endif //SSODC_UTILS_DAEMON_HPP_