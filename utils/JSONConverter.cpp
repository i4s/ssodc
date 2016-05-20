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

int JSONConverter::CreateSimpleRequest(int request, std::string& outputJson) {
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

int JSONConverter::MapWithVectorValueToString(std::map<int, std::vector<int>>& inputMap,
        int request, std::string& outputJson) {
    Json::Value root;
    Json::Value jsonMap;
    std::map<int, std::vector<int>>::const_iterator it = inputMap.begin();
    std::map<int, std::vector<int>>::const_iterator end = inputMap.end();
    for (; it != end; it++) {
        Json::Value currentElement;
        Json::Value jsonVector;
        std::vector<int> vector= it->second;
        for(auto v : vector) {
            jsonVector.append(std::to_string(v));
        }
        currentElement[MAP_KEY] = it->first;
        currentElement[MAP_VALUE] = jsonVector;
        jsonMap.append(currentElement);
    }
    root[REQUEST_TYPE] = request;
    root[KEY_TYPE] = typeid(inputMap.begin()->first).name();
    root[VALUE_TYPE] = typeid((inputMap.begin()->second).back()).name();
    root[DATA] = jsonMap;
    Json::StyledWriter writer;
    outputJson = writer.write(root);
    return 0;
}

int JSONConverter::StringToMapWithVector(std::string& inputJSON,
        std::map<int, std::vector<int>>& resultMap) {
    Json::Value root;
    Json::Reader reader;
    if(!reader.parse(inputJSON, root)) {
        //TODO Logging
    }
    for(auto pair: root[DATA]) {
        std::vector<int> vector;
        for(auto vectorElement: pair[MAP_VALUE]) {
            vector.push_back(std::stoi(vectorElement.asString()));
        }
        resultMap.insert(std::pair<int, std::vector<int>>(pair[MAP_KEY].asInt(), vector));
    }
    return 0;
}

int JSONConverter::CreateNewTask(TaskInfo& taskInfo, int request, std::string& outputJson) {
    Json::Value root;
    root[REQUEST_TYPE] = request;
    root[TI_ID] = taskInfo.GetId();
    root[TI_TYPE] = taskInfo.GetType();
    root[TI_CODE_PATH] = taskInfo.GetCodePath();
    root[TI_DATA_PATH] = taskInfo.GetDataPath();
    root[TI_EXECUTABLE_PATH] = taskInfo.GetExecutablePath();
    Json::StyledWriter writer;
    outputJson = writer.write(root);
    return 0;
}

int JSONConverter::GetNewTask(std::string& inputJSON, ssodc::utils::TaskInfo& taskInfo) {
    Json::Value root;
    Json::Value jsonTaskInfo;
    Json::Reader reader;
    if(!reader.parse(inputJSON, root)) {
        //TODO Logging
    }
    taskInfo = ssodc::utils::TaskInfo(root[TI_ID].asInt(),
                                      static_cast<ssodc::utils::TaskType>(root[TI_TYPE].asInt()),
                                      root[TI_DATA_PATH].asString(), root[TI_CODE_PATH].asString(),
                                      root[TI_EXECUTABLE_PATH].asString());
    return 0;
}

} /* namespace utils */
} /* namespace ssodc */
