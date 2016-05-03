#include <fstream>

#include "SourceBuilder.hpp"

namespace ssodc {
namespace utils {

std::string SourceBuilder::Build(std::deque<std::string> fileNames) {
    char buffer[BUFFER_SIZE];
    std::string outputMessage = "";
    std::string command = GenerateCommand(fileNames);
    std::shared_ptr<FILE> compiler(popen(command.c_str(), "r"), pclose);
    if(!compiler) {
        //TODO: Add logging
        return "popen() failed";
    }
    while (!feof(compiler.get())) {
        if (fgets(buffer, BUFFER_SIZE, compiler.get()) != NULL) {
            outputMessage += buffer;
        }
    }
    return outputMessage;
}

std::string SourceBuilder::GenerateCommand(std::deque<std::string> fileNames) {
    std::string command = "/usr/bin/g++ 2>&1 -std=c++14";
    for (const auto& name : fileNames) {
        command.append(" ");
        command.append(name);
    }
    return command;
}

} /* namespace utils */
} /* namespace ssodc */