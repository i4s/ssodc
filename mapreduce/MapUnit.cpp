#include <chrono>
#include <fstream>

#include "MapUnit.hpp"
#include "TextMapper.hpp"
#include "ImageMapper.hpp"
#include "SourceBuilder.hpp"

namespace ssodc {
namespace mapreduce {

MapUnit::MapUnit() : ssodc::utils::Daemon() {
    m_listener = std::unique_ptr<ssodc::ipc::IProcessMQ>(new ssodc::ipc::IProcessMQ("tcp://*:7777"));
    m_threadListener = std::thread(&MapUnit::PortListener, this);
    Log("constructor");
}

MapUnit::~MapUnit() {
    Log("Destructor");
    if(m_threadListener.joinable()) {
        m_threadListener.join();
    }
}

int MapUnit::Run() {
    while (!m_terminate) {
        Log("Run:while");
        if (!m_tasks.empty()) {
            Log("Run:get new task");
            ssodc::utils::TaskInfo taskInfo = m_tasks.front();
            //UpdateTaskInfo(taskInfo);
            std::map<int, std::string> partPath;
            switch (taskInfo.GetType()) {
            case ssodc::utils::TaskType::Text: {
                std::string dataPath = taskInfo.GetDataPath();
                ssodc::mapreduce::TextMapper textMapper(dataPath);
                textMapper.Mapping(4);
                partPath = textMapper.GetPartPath();
            }
            break;
            case ssodc::utils::TaskType::Image: {
                std::string dataPath = taskInfo.GetDataPath();
                ssodc::mapreduce::ImageMapper imageMapper(dataPath);
                imageMapper.Mapping(4);
                partPath = imageMapper.GetPartPath();
            }
            break;
            }
            BuildSource(taskInfo);
            SaveMaps(partPath, taskInfo);
            FinishWork(taskInfo);
            m_tasks.pop_front();
        }
        std::chrono::seconds duration(5);
        std::this_thread::sleep_for(duration);
    }
    Stop();
    return 0;
}

int MapUnit::PortListener() {
    while(!m_terminate) {
        m_listener->Listen(std::bind(&ssodc::mapreduce::MapUnit::MessageHandler,
                                     this, std::placeholders::_1));
    }
    return 0;
}

std::string MapUnit::MessageHandler(std::string inputMessage) {
    Log("MessageHandler:new message");
    int requestType = ssodc::utils::JSONConverter::GetRequestType(inputMessage);
    switch (requestType) {
    case ssodc::utils::request::NEW_TASK: {
        ssodc::utils::TaskInfo taskInfo;
        ssodc::utils::JSONConverter::GetTaskInfo(inputMessage, taskInfo);
        m_tasks.push_back(taskInfo);
        return "All is good, task will be solved";
    }
    }
    return "";
}

void MapUnit::Log(const char* a) {
    std::ofstream newPart("/home/evgenii/Courser/22.05V2/ssodc/log.txt", std::ofstream::app);
    if(newPart.is_open()) {
        newPart << a << std::endl;
        newPart.close();
    }
}

int MapUnit::SaveMaps(std::map<int, std::string>& partPath, ssodc::utils::TaskInfo& taskInfo) {
    std::string pathMessage;
    ssodc::utils::JSONConverter::CreateRequest(ssodc::utils::request::SAVE_BASIC_MAP,
            pathMessage);
    ssodc::utils::JSONConverter::PutTaskInfo(taskInfo, pathMessage);
    ssodc::utils::JSONConverter::MapToString(partPath, pathMessage);
    std::ofstream path("/home/evgenii/Courser/22.05V2/ssodc/partpath.txt", std::ofstream::out);
    if(path.is_open()) {
        path << pathMessage << std::endl;
        path.close();
    }
    return 0;
}

/*
int MapUnit::SaveMaps(std::map<int, std::string>& partPath, ssodc::utils::TaskInfo& taskInfo) {
    std::string pathMessage;
    std::string reduceMessage;
    ssodc::utils::JSONConverter::CreateRequest(ssodc::utils::request::SAVE_BASIC_MAP,
        pathMessage);
    ssodc::utils::JSONConverter::PutTaskInfo(taskInfo, pathMessage);
    ssodc::utils::JSONConverter::MapToString(partPath, pathMessage);
    ssodc::ipc::IProcessMQ database("tcp://127.0.0.1:7778");
    database.Send(pathMessage);
    return 0;
}*/

int MapUnit::UpdateTaskInfo(ssodc::utils::TaskInfo& taskInfo) {
    taskInfo.SetStatus(ssodc::utils::TaskStatus::Mapping);
    std::string taskMessage;
    ssodc::utils::JSONConverter::CreateRequest(
        ssodc::utils::request::UPDATE_TASK_INFO, taskMessage);
    ssodc::utils::JSONConverter::PutTaskInfo(taskInfo, taskMessage);
    ssodc::ipc::IProcessMQ database("tcp://127.0.0.1:7778");
    database.Send(taskMessage);
    return 0;
}

int MapUnit::FinishWork(ssodc::utils::TaskInfo& taskInfo) {
    std::string taskMessage;
    ssodc::utils::JSONConverter::CreateRequest(
        ssodc::utils::request::NEW_TASK, taskMessage);
    ssodc::utils::JSONConverter::PutTaskInfo(taskInfo, taskMessage);
    ssodc::ipc::IProcessMQ taskExecutor("tcp://127.0.0.1:7780");
    taskExecutor.Send(taskMessage);
    return 0;
}


int MapUnit::Stop() {
    Log("Stop:start");
    std::string exitMessage;
    ssodc::utils::JSONConverter::CreateRequest(
        ssodc::utils::request::CLOSE_CONNECTION, exitMessage);
    ssodc::ipc::IProcessMQ forMyself("tcp://127.0.0.1:7777");
    forMyself.Send(exitMessage);
    Log("Stop:finished");
    return 0;
}

int MapUnit::BuildSource(ssodc::utils::TaskInfo& taskInfo) {
    Log("BuildSource:start");
    std::string inputFileName = taskInfo.GetCodePath();
    if(!inputFileName.empty()) {
        std::string outputFileName("mnt/ssodcdata/");
        outputFileName.append(std::to_string(taskInfo.GetId()));
        outputFileName.append("-executable");
        Log(outputFileName.c_str());
        ssodc::utils::SourceBuilder::Build(inputFileName, outputFileName);
        taskInfo.SetExecutablePath(outputFileName);
    }
    Log("BuildSource:finished");
    return 0;
}

} /* namespace mapreduce */
} /* namespace ssodc */