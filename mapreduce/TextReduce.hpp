#pragma once

#include <string>

#include "ReduceInterface.hpp"

namespace ssodc {
namespace mapreduce {

class TextReduce : public ReduceInterface {
public:
    TextReduce(std::map<int, std::string>&, std::map<int, std::vector<int>>&);
    ~TextReduce();

    int Reducing();
    std::string GetProcessedData();
private:
    std::string m_processedData;
    std::map<int, std::string> m_partPath;
    std::map<int, std::vector<int>> m_partReduce;
};

} /* namespace mapreduce */
} /* namespace ssodc */