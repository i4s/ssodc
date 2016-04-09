#ifndef SSODC_DIVIDER_DAEMON_H_
#define SSODC_DIVIDER_DAEMON_H_

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

#endif //SSODC_DIVIDER_DAEMON_H_