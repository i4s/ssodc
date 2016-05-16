#pragma once

#include <string>

namespace ssodc {
namespace utils {

const int BUFFER_SIZE = 1024;
const std::string PWD_COMMAND = "pwd";

class DirectoryInfo {
public:
    static std::string GetWorkingDirectory();
};

} /* namespace utils */
} /* namespace ssodc */