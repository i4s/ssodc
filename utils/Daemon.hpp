#ifndef SSODC_UTILS_DAEMON_HPP_
#define SSODC_UTILS_DAEMON_HPP_

namespace ssodc {
namespace utils {
class daemon {
protected:
    static bool m_terminate;
public:
    daemon();
    ~daemon();
    virtual int daemonize();
private:
    static void terminateHandler(int);
};
}
}

#endif //SSODC_UTILS_DAEMON_HPP_