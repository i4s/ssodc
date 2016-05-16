#pragma once

#include <string>

namespace ssodc {
namespace utils {

const std::string DIRECTORY_TO_SAVE = "/mnt/ssodcdata/";
const std::string TXT_FILE_EXTENSION = ".txt";

class FileWorker {
public:
    static u_int64_t FileLenght(std::string&);
    
    static std::string GenerateFileName();
    static std::string GenerateFileName(int);
};

} /* namespace utils */
} /* namespace ssodc */