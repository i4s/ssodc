#pragma once

#include "JSONConverter.hpp"

namespace ssodc {
namespace utils {


template<>
int JSONConverter::StringToMap<int, int>(std::string& inputJson,
        std::map<int, int>& outputMap) {
    Json::Value root;
    Json::Reader reader;
    if(!reader.parse(inputJson, root)) {
        //Logging, where are you?
    }
    for(auto r: root) {
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
        //Logging, where are you?
    }
    for(auto r: root) {
        outputMap.insert(std::pair<int, std::string>(r[MAP_KEY].asInt(),
                         r[MAP_VALUE].asString()));
    }
    return 0;
}

int JSONConverter::MapWithVectorValueToString(std::map<int, std::vector<int>>& inputMap,
        std::string& outputJson) {
    Json::Value root;
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
        root.append(currentElement);
    }
    Json::StyledWriter writer;
    outputJson = writer.write(root);
    return 0;
}

int JSONConverter::StringToMapWithVector(std::string& inputJSON,
        std::map<int, std::vector<int>>& resultMap) {
    Json::Value root;
    Json::Reader reader;
    if(!reader.parse(inputJSON, root)) {
        //Logging, where are you?
    }
    for(auto pair: root) {
        std::vector<int> vector;
        for(auto vectorElement: pair[MAP_VALUE]) {
            vector.push_back(std::stoi(vectorElement.asString()));
        }
        resultMap.insert(std::pair<int, std::vector<int>>(pair[MAP_KEY].asInt(), vector));
    }

    return 0;
}


} /* namespace utils */
} /* namespace ssodc */
