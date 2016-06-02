#include <ios>
#include <chrono>
#include <thread>
#include <string>
#include <fstream>

#include "ReduceUnit.hpp"
#include "TextReduce.hpp"
#include "ImageReduce.hpp"
#include "JSONConverter.hpp"

namespace ssodc {
namespace mapreduce {

ReduceUnit::ReduceUnit() : ssodc::utils::Daemon() {
    m_listener = std::unique_ptr<ssodc::ipc::IProcessMQ>(new ssodc::ipc::IProcessMQ("tcp://*:7780"));
    m_threadListener = std::thread(&ReduceUnit::PortListener, this);
    Log("constructor");
}

ReduceUnit::~ReduceUnit() {
    Log("Destructor");
    if(m_threadListener.joinable()) {
        m_threadListener.join();
    }
}

int ReduceUnit::Run() {
    while (!m_terminate) {
        Log("Run:while");
        if (!m_tasks.empty()) {
            Log("Run:get new task");
            ssodc::utils::TaskInfo taskInfo = m_tasks.front();
            taskInfo.SetStatus(ssodc::utils::TaskStatus::Mapping);
            //UpdateTaskInfo(taskInfo);
            std::map<int, std::string> partPath;
            GetMaps(partPath, taskInfo);
            switch (taskInfo.GetType()) {
            case ssodc::utils::TaskType::Text: {
                ssodc::mapreduce::TextReduce textReduce(partPath);
                textReduce.Reducing();
                std::string outputFile = textReduce.GetProcessedData();
                taskInfo.SetDataPath(outputFile);
            }
            break;
            case ssodc::utils::TaskType::Image: {
                ssodc::mapreduce::ImageReduce imageReduce(partPath);
                imageReduce.Reducing();
                std::string outputFile = imageReduce.GetProcessedData();
                taskInfo.SetDataPath(outputFile);
            }
            break;
            }
            taskInfo.SetStatus(ssodc::utils::TaskStatus::Finished);
            //UpdateTaskInfo(taskInfo);
            m_tasks.pop_front();
        }
        std::chrono::seconds duration(5);
        std::this_thread::sleep_for(duration);
    }
    Stop();
    return 0;
}

int ReduceUnit::PortListener() {
    while(!m_terminate) {
        m_listener->Listen(std::bind(&ssodc::mapreduce::ReduceUnit::MessageHandler,
                                     this, std::placeholders::_1));
    }
    return 0;
}

std::string ReduceUnit::MessageHandler(std::string inputMessage) {
    Log("MessageHandler:new message");
    int requestType = ssodc::utils::JSONConverter::GetRequestType(inputMessage);
    switch (requestType) {
    case ssodc::utils::request::NEW_TASK: {
        ssodc::utils::TaskInfo taskInfo;
        ssodc::utils::JSONConverter::GetTaskInfo(inputMessage, taskInfo);
        m_tasks.push_back(taskInfo);
        return "";
    }
    }
    return "";
}

void ReduceUnit::Log(const char* a) {
    std::ofstream newPart("/home/evgenii/Courser/22.05V2/ssodc/logreduce.txt", std::ofstream::app);
    if(newPart.is_open()) {
        newPart << a << std::endl;
        newPart.close();
    }
}

int ReduceUnit::GetMaps(std::map<int, std::string>& partPath, ssodc::utils::TaskInfo& taskInfo) {
    std::string pathMessage;
    std::ifstream path("/home/evgenii/Courser/22.05V2/ssodc/partpath.txt", std::ios::binary);
    if(path.is_open()) {
        path.seekg( 0, std::ios_base::end);
        std::ifstream::pos_type len = path.tellg();
        path.seekg(0);
        pathMessage.resize(len);
        path.read((char*)pathMessage.data(), len);
        path.close();
    }
    ssodc::utils::JSONConverter::StringToMap(pathMessage, partPath);
    return 0;
}

/*
int ReduceUnit::GetMaps(std::map<int, std::string>& partPath, ssodc::utils::TaskInfo& taskInfo) {
    std::string pathMessage;
    std::string inputPartPath;
    ssodc::ipc::IProcessMQ database("tcp://127.0.0.1:7778");
    ssodc::utils::JSONConverter::CreateRequest(ssodc::utils::request::GET_BASIC_MAP,
        pathMessage);
    ssodc::utils::JSONConverter::PutTaskInfo(taskInfo, pathMessage);
    database.Send(pathMessage);
    database.Recv(inputPartPath);
    ssodc::utils::JSONConverter::StringToMap(inputPartPath, partPath);
    return 0;
}*/

int ReduceUnit::UpdateTaskInfo(ssodc::utils::TaskInfo& taskInfo) {
    taskInfo.SetStatus(ssodc::utils::TaskStatus::Mapping);
    std::string taskMessage;
    ssodc::utils::JSONConverter::CreateRequest(
        ssodc::utils::request::UPDATE_TASK_INFO, taskMessage);
    ssodc::utils::JSONConverter::PutTaskInfo(taskInfo, taskMessage);
    ssodc::ipc::IProcessMQ database("tcp://127.0.0.1:7778");
    database.Send(taskMessage);
    return 0;
}

/*   i don't sure, that this method will be usefull*/
int ReduceUnit::FinishWork(ssodc::utils::TaskInfo& taskInfo) {
    std::string taskMessage;
    ssodc::utils::JSONConverter::CreateRequest(
        ssodc::utils::request::UPDATE_TASK_INFO, taskMessage);
    ssodc::utils::JSONConverter::PutTaskInfo(taskInfo, taskMessage);
    ssodc::ipc::IProcessMQ taskExecutor("tcp://127.0.0.1:7779");
    taskExecutor.Send(taskMessage);
    return 0;
}


int ReduceUnit::Stop() {
    Log("Stop:start");
    std::string exitMessage;
    ssodc::utils::JSONConverter::CreateRequest(
        ssodc::utils::request::CLOSE_CONNECTION, exitMessage);
    ssodc::ipc::IProcessMQ forMyself("tcp://127.0.0.1:7780");
    forMyself.Send(exitMessage);
    Log("Stop:finished");
    return 0;
}

} /* namespace mapreduce */
} /* namespace ssodc */