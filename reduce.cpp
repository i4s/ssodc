#include "ReduceUnit.hpp"
#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <memory>

int main() {
    std::unique_ptr<ssodc::mapreduce::ReduceUnit> mu
        = std::unique_ptr<ssodc::mapreduce::ReduceUnit>(new ssodc::mapreduce::ReduceUnit());
    mu->Start();
    return 0;
}