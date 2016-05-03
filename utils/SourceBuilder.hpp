#pragma once

#include <deque>
#include <memory>
#include <string>

namespace ssodc {
namespace utils {

const int BUFFER_SIZE = 1000;

class SourceBuilder {
public:
    static std::string Build(std::deque<std::string>);
private:
    static std::string GenerateCommand(std::deque<std::string>);
};
} /* namespace utils */
} /* namespace ssodc */
