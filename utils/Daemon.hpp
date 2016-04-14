#pragma once

namespace ssodc {
namespace utils {
class Daemon {
	public:
    Daemon();
    ~Daemon();
    virtual int Run() = 0;
    int Start();
protected:
    static bool m_terminate;
private:
    static void TerminateHandler(int);
};
} /* namespace utils */
} /* namespace ssodc */
