#include "MapUnit.hpp"
#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <memory>

int main() {
    std::unique_ptr<ssodc::mapreduce::MapUnit> mu
        = std::unique_ptr<ssodc::mapreduce::MapUnit>(new ssodc::mapreduce::MapUnit());
    mu->Start();
    return 0;
}