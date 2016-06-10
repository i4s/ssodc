#include <fstream>

#include "SourceBuilder.hpp"

namespace ssodc {
namespace utils {

int SourceBuilder::BuildLinux(std::string& fileNames, std::string& outputFileName) {
    char buffer[BUFFER_SIZE];
    std::string outputMessage = "";
    std::string command = GenerateCommandLinux(fileNames, outputFileName);
    std::shared_ptr<FILE> compiler(popen(command.c_str(), "r"), pclose);
    if(!compiler) {
        //TODO: Add logging
        return -1;
    }
    while (!feof(compiler.get())) {
        if (fgets(buffer, BUFFER_SIZE, compiler.get()) != NULL) {
            outputMessage += buffer;
        }
    }
    return 0;
}

int SourceBuilder::BuildWin(std::string& fileNames, std::string& outputFileName) {
    char buffer[BUFFER_SIZE];
    std::string outputMessage = "";
    std::string command = GenerateCommandWin(fileNames, outputFileName);
    std::shared_ptr<FILE> compiler(popen(command.c_str(), "r"), pclose);
    if(!compiler) {
        //TODO: Add logging
        return -1;
    }
    while (!feof(compiler.get())) {
        if (fgets(buffer, BUFFER_SIZE, compiler.get()) != NULL) {
            outputMessage += buffer;
        }
    }
    return 0;
}

std::string SourceBuilder::GenerateCommandLinux(std::string& fileNames, std::string& outputFileName) {
    std::string command = "/usr/bin/g++ 2>&1 -std=c++14 ";
    command.append(fileNames);
    command.append(" -o ");
    command.append(outputFileName);
    return command;
}

std::string SourceBuilder::GenerateCommandWin(std::string& fileNames, std::string& outputFileName) {
    std::string command = "/usr/bin/i586-mingw32msvc-g++ 2>&1-std=c++14 ";
    command.append(fileNames);
    command.append(" -o ");
    command.append(outputFileName);
    return command;
}

} /* namespace utils */
} /* namespace ssodc */