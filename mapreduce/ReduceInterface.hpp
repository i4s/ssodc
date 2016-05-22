#pragma once 

#include <map>
#include <string>
#include <vector>

namespace ssodc {
namespace mapreduce {

class ReduceInterface {
public:
    virtual int Reducing() = 0;
};

} /* namespace mapreduce */
} /* namespace ssodc */