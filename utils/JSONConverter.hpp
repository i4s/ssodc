#pragma once

#include <map>
#include <string>
#include <vector>
#include <typeinfo>
#include <jsoncpp/json/json.h>

#include "TaskInfo.hpp"

namespace ssodc {
namespace utils {

const std::string DATA = "Data";
const std::string INFO = "Info";
const std::string MAP_KEY = "Key";
const std::string MAP_VALUE = "Value";
const std::string KEY_TYPE = "KeyType";
const std::string VALUE_TYPE = "ValueType";
const std::string REQUEST_TYPE = "Request";

const std::string TI_ID = "TaskInfoID";
const std::string TI_TYPE = "TaskInfoType";
const std::string TI_STATUS = "TaskInfoStatus";
const std::string TI_CODE_PATH = "TaskInfoCodePath";
const std::string TI_DATA_PATH = "TaskInfoDataPath";
const std::string TI_EXECUTABLE_PATH = "TaskInfoExecutablePath";

class JSONConverter
{
public:
    static int GetRequestType(std::string&);
    static int CreateRequest(int, std::string&);
    static std::string GetMapKeyType(std::string&);
    static std::string GetMapValueType(std::string&);
    static int PutTaskInfo(TaskInfo&, std::string&);
    static int GetTaskInfo(std::string&, ssodc::utils::TaskInfo&);

    template <class Key, class Value>
    static int MapToString(std::map<Key, Value>&, std::string&);
    template <class Key, class Value>
    static int StringToMap(std::string&, std::map<Key, Value>&);
};

template<class Key, class Value>
int JSONConverter::MapToString(std::map<Key, Value>& inputMap, std::string& outputJson) {
    Json::Value root;
    Json::Reader reader;
    if(!reader.parse(outputJson, root)) {
        //TODO Logging
    }
    Json::Value jsonMap;
    typename std::map<Key, Value>::const_iterator it = inputMap.begin();
    typename std::map<Key, Value>::const_iterator end = inputMap.end();
    for ( ; it != end; ++it) {
        Json::Value currentElement;
        Json::Value jsonVector;
        currentElement[MAP_KEY] = it->first;
        currentElement[MAP_VALUE] = it->second;
        jsonMap.append(currentElement);
    }
    root[KEY_TYPE] = typeid(inputMap.begin()->first).name();
    root[VALUE_TYPE] = typeid(inputMap.begin()->second).name();
    root[DATA] = jsonMap;
    Json::StyledWriter writer;
    outputJson = writer.write(root);
    return 0;
}

} /* namespace utils */
} /* namespace ssodc */
