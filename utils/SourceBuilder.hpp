#pragma once

#include <memory>
#include <string>

namespace ssodc {
namespace utils {

const int BUFFER_SIZE = 1000;

class SourceBuilder {
public:
    static int BuildLinux(std::string&, std::string&);
    static int BuildWin(std::string&, std::string&);
private:
    static std::string GenerateCommandLinux(std::string&, std::string&);
    static std::string GenerateCommandWin(std::string&, std::string&);
};
} /* namespace utils */
} /* namespace ssodc */
