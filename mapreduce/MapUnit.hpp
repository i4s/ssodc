#pragma once

#include <map>
#include <list>
#include <memory>
#include <string>
#include <thread>

#include "Daemon.hpp"
#include "Request.hpp"
#include "TaskInfo.hpp"
#include "IProcessMQ.hpp"
#include "JSONConverter.hpp"

namespace ssodc {
namespace mapreduce {

class MapUnit : public ssodc::utils::Daemon {
public:
    MapUnit();
    ~MapUnit();

    int Run();
    int Stop();
    void Log(const char*); //TODO Delete, when logging will be implemented
    int PortListener();
    int FinishWork(ssodc::utils::TaskInfo&);
    std::string MessageHandler(std::string);
    int BuildSource(ssodc::utils::TaskInfo&);
    int UpdateTaskInfo(ssodc::utils::TaskInfo&);
    int SaveMaps(std::map<int, std::string>&, ssodc::utils::TaskInfo&);
private:
    std::thread m_threadListener;
    std::list<ssodc::utils::TaskInfo> m_tasks;
    std::unique_ptr<ssodc::ipc::IProcessMQ> m_listener;
};

} /* namespace mapreduce */
} /* namespace ssodc */