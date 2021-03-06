#pragma once

#include <string>

#include "ReduceInterface.hpp"

namespace ssodc {
namespace mapreduce {

class TextReduce : public ReduceInterface {
public:
    TextReduce(std::map<int, std::string>&);
    ~TextReduce();

    int Reducing();
    std::string GetProcessedData();
private:
    std::string m_processedData;
    std::map<int, std::string> m_partPath;
};

} /* namespace mapreduce */
} /* namespace ssodc */