#pragma once

#include <map>
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>

namespace ssodc {
namespace utils {

const std::string MAP_KEY = "Key";
const std::string MAP_VALUE = "Value";

class JSONConverter
{
public:
    template<class Key, class Value>
    static int MapToString(std::map<Key, Value>&, std::string&);
    template<class Key, class Value>
    static int StringToMap(std::string&, std::map<Key, Value>&);
    static int StringToMapWithVector(std::string&, std::map<int, std::vector<int>>&);
    static int MapWithVectorValueToString(std::map<int, std::vector<int>>&, std::string&);
};

template<class Key, class Value>
int JSONConverter::MapToString(std::map<Key, Value>& inputMap, std::string& outputJson) {
    Json::Value root;
    typename std::map<Key, Value>::const_iterator it = inputMap.begin();
    typename std::map<Key, Value>::const_iterator end = inputMap.end();
    for ( ; it != end; ++it) {
        Json::Value currentElement;
        Json::Value jsonVector;
        currentElement[MAP_KEY] = it->first;
        currentElement[MAP_VALUE] = it->second;
        root.append(currentElement);
    }
    Json::StyledWriter writer;
    outputJson = writer.write(root);
    return 0;
}

} /* namespace utils */
} /* namespace ssodc */
