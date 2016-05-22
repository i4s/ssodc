#include "TaskInfo.hpp"

namespace ssodc {
namespace utils {

TaskInfo::TaskInfo() : m_id(0),
    m_type(TaskType::Text), m_status(TaskStatus::Unknown), m_datapath(""),
    m_codepath(""), m_executablepath("") {
}

TaskInfo::TaskInfo(int id, TaskType type, TaskStatus status, std::string datapath,
                   std::string codepath, std::string executablepath) : m_id(id),
    m_type(type), m_status(status), m_datapath(datapath),
    m_codepath(codepath), m_executablepath(executablepath) {
}

TaskInfo::~TaskInfo() {
}

int TaskInfo::GetId() {
    return m_id;
}

TaskType TaskInfo::GetType() {
    return m_type;
}

TaskStatus TaskInfo::GetStatus() {
	return m_status;
}

std::string TaskInfo::GetDataPath() {
    return m_datapath;
}

std::string TaskInfo::GetCodePath() {
    return m_codepath;
}

std::string TaskInfo::GetExecutablePath() {
    return m_executablepath;
}

void TaskInfo::SetStatus(TaskStatus status) {
	m_status = status;
}

void TaskInfo::SetDataPath(std::string& data) {
    m_datapath = data;
}

void TaskInfo::SetExecutablePath(std::string& executablepath) {
    m_executablepath = executablepath;
}

} /* namespace utils */
} /* namespace ssodc */