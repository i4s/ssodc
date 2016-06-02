#include "JSONConverter.hpp"

namespace ssodc {
namespace utils {

int JSONConverter::GetRequestType(std::string& inputJson) {
    Json::Value root;
    Json::Reader reader;
    if(!reader.parse(inputJson, root)) {
        //Logging, where are you?
    }
    return root[REQUEST_TYPE].asInt();
}

std::string JSONConverter::GetMapKeyType(std::string& inputJson) {
    Json::Value root;
    Json::Reader reader;
    if(!reader.parse(inputJson, root)) {
        //TODO Logging
    }
    return root[KEY_TYPE].asString();
}

std::string JSONConverter::GetMapValueType(std::string& inputJson) {
    Json::Value root;
    Json::Reader reader;
    if(!reader.parse(inputJson, root)) {
        //TODO Logging
    }
    return root[VALUE_TYPE].asString();
}

int JSONConverter::CreateRequest(int request, std::string& outputJson) {
    Json::Value root;
    root[REQUEST_TYPE] = request;
    Json::StyledWriter writer;
    outputJson = writer.write(root);
    return 0;
}

template<>
int JSONConverter::StringToMap<int, int>(std::string& inputJson,
        std::map<int, int>& outputMap) {
    Json::Value root;
    Json::Reader reader;
    if(!reader.parse(inputJson, root)) {
        //TODO Logging
    }
    for(auto r: root[DATA]) {
        outputMap.insert(std::pair<int, int>(r[MAP_KEY].asInt(), r[MAP_VALUE].asInt()));
    }
    return 0;
}

template<>
int JSONConverter::StringToMap<int, std::string>(std::string& inputJson,
        std::map<int, std::string>& outputMap) {
    Json::Value root;
    Json::Reader reader;
    if(!reader.parse(inputJson, root)) {
        //TODO Logging
    }
    for(auto r: root[DATA]) {
        outputMap.insert(std::pair<int, std::string>(r[MAP_KEY].asInt(),
                         r[MAP_VALUE].asString()));
    }
    return 0;
}

int JSONConverter::PutTaskInfo(TaskInfo& taskInfo, std::string& outputJson) {
    Json::Value root;
    Json::Reader reader;
    if(!reader.parse(outputJson, root)) {
        //TODO Logging
    }
    Json::Value jsonTaskInfo;
    jsonTaskInfo[TI_ID] = taskInfo.GetId();
    jsonTaskInfo[TI_TYPE] = taskInfo.GetType();
    jsonTaskInfo[TI_STATUS] = taskInfo.GetStatus();
    jsonTaskInfo[TI_CODE_PATH] = taskInfo.GetCodePath();
    jsonTaskInfo[TI_DATA_PATH] = taskInfo.GetDataPath();
    jsonTaskInfo[TI_EXECUTABLE_PATH] = taskInfo.GetExecutablePath();
    root[INFO] = jsonTaskInfo;
    Json::StyledWriter writer;
    outputJson = writer.write(root);
    return 0;
}

int JSONConverter::GetTaskInfo(std::string& inputJSON, ssodc::utils::TaskInfo& taskInfo) {
    Json::Value root;
    Json::Value jsonTaskInfo;
    Json::Reader reader;
    if(!reader.parse(inputJSON, root)) {
        //TODO Logging
    }
    jsonTaskInfo = root[INFO];
    taskInfo = ssodc::utils::TaskInfo(jsonTaskInfo[TI_ID].asInt(),
                                      static_cast<ssodc::utils::TaskType>(jsonTaskInfo[TI_TYPE].asInt()),
                                      static_cast<ssodc::utils::TaskStatus>(jsonTaskInfo[TI_STATUS].asInt()),
                                      jsonTaskInfo[TI_DATA_PATH].asString(), jsonTaskInfo[TI_CODE_PATH].asString(),
                                      jsonTaskInfo[TI_EXECUTABLE_PATH].asString());
    return 0;
}

} /* namespace utils */
} /* namespace ssodc */
