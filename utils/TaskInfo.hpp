#pragma once

#include <string>

namespace ssodc {
namespace utils {

enum TaskType {
    Text = 1,
    Image
};

enum TaskStatus {
    Unknown = 0,
    Waiting,
    Mapping,
    Processing,
    Reducing,
    Finished
};

class TaskInfo {
public:
    TaskInfo();
    TaskInfo(int id, TaskType type, TaskStatus status, std::string datapath,
             std::string codepath = "", std::string executablepath = "");
    ~TaskInfo();

    int GetId();
    TaskType GetType();
    TaskStatus GetStatus();
    std::string GetDataPath();
    std::string GetCodePath();
    std::string GetExecutablePath();

    void SetStatus(TaskStatus);
    void SetDataPath(std::string&);
    void SetExecutablePath(std::string&);
private:
    int m_id;
    TaskType m_type;
    TaskStatus m_status;
    std::string m_datapath;
    std::string m_codepath;
    std::string m_executablepath;
};

} /* namespace utils */
} /* namespace ssodc */