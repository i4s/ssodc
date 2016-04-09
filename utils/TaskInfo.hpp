#ifndef SSODC_UTILS_TASKINFO_HPP_
#define SSODC_UTILS_TASKINFO_HPP_

#include <string>

namespace ssodc {
namespace utils {
class taskinfo {
private:
    unsigned int m_id;
    unsigned int m_type;
    std::string m_datapath;
    std::string m_codepath;
public:
    taskinfo();
    taskinfo(int, int, std::string, std::string);
    taskinfo(const taskinfo&);
    ~taskinfo();

    taskinfo& operator=(const taskinfo&);
    unsigned int getId();
    unsigned int getType();
    std::string getDataPath();
    std::string getCodePath();
    int getCodePath(std::string&);
};
}
}

#endif //SSODC_UTILS_TASKINFO_HPP_