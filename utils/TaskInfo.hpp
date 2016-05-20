#pragma once

#include <string>

namespace ssodc {
namespace utils {

enum TaskType {
    Text = 1,
    BitMap = 2
};

class TaskInfo {
public:
    TaskInfo();
    TaskInfo(int id, TaskType type, std::string datapath,
             std::string codepath = "", std::string executablepath = "");
    ~TaskInfo();

    int GetId();
    TaskType GetType();
    std::string GetDataPath();
    std::string GetCodePath();
    std::string GetExecutablePath();
    void SetExecutablePath(std::string&);
private:
    int m_id;
    TaskType m_type;
    std::string m_datapath;
    std::string m_codepath;
    std::string m_executablepath;
};

} /* namespace utils */
} /* namespace ssodc */