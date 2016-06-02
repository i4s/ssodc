#pragma once

#include <string>

#include "ReduceInterface.hpp"

namespace ssodc {
namespace mapreduce {

class ImageReduce : public ReduceInterface {
public:
    ImageReduce(std::map<int, std::string>&);
    ~ImageReduce();

    int Reducing();
    std::string GetProcessedData();
private:
    std::string m_processedData;
    std::map<int, std::string> m_partPath;
};

} /* namespace mapreduce */
} /* namespace ssodc */