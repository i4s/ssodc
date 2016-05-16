#include <memory>

#include "DirectoryInfo.hpp"

namespace ssodc {
namespace utils {

std::string DirectoryInfo::GetWorkingDirectory() {
    char buffer[BUFFER_SIZE];
    std::string outputMessage;
    std::shared_ptr<FILE> compiler(popen(PWD_COMMAND.c_str(), "r"), pclose);
    if(!compiler) {
        //TODO: Add logging
        return "popen() failed";
    }
    while (!feof(compiler.get())) {
        if (fgets(buffer, BUFFER_SIZE, compiler.get()) != NULL) {
            outputMessage += buffer;
        }
    }
    outputMessage.insert(outputMessage.size() - 1, "/");
    outputMessage.erase(outputMessage.size() - 1);
    return outputMessage;
}

} /* namespace utils */
} /* namespace ssodc */