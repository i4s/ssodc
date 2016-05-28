#pragma once

#include <memory>
#include <string>

namespace ssodc {
namespace utils {

const int BUFFER_SIZE = 1000;

class SourceBuilder {
public:
    static int Build(std::string&, std::string&);
private:
    static std::string GenerateCommand(std::string&, std::string&);
};
} /* namespace utils */
} /* namespace ssodc */
