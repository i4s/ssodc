#pragma once

#include <map>
#include <string>
#include <vector>

namespace ssodc {
namespace mapreduce {

class MapInterface {
public:
    virtual int Mapping(int) = 0;
    virtual std::map<int, std::string> GetPartPath() = 0;
    virtual std::map<int, std::vector<int>> GetPartReduce() = 0;
};

} /* namespace mapreduce */
} /* namespace ssodc */