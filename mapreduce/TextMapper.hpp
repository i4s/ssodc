#pragma once

#include "MapperInterface.hpp"

namespace ssodc {
namespace mapreduce {

class TextMapper : public MapInterface {
    std::string m_filePath;
    std::map<int, std::string> m_partPath;
    std::map<int, std::vector<int>> m_partReduce;
public:
    TextMapper(std::string&);
    ~TextMapper();

    int Mapping(int);
    std::map<int, std::string> GetPartPath();
    std::map<int, std::vector<int>> GetPartReduce();
};

} /* namespace mapreduce */
} /* namespace ssodc */