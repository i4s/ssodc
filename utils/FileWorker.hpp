#pragma once

#include <string>

namespace ssodc {
namespace utils {

const std::string DIRECTORY_TO_SAVE = "/mnt/ssodcdata/";
const std::string TXT_FILE_EXTENSION = ".txt";
const std::string BMP_FILE_EXTANSION = ".bmp";
const std::string JPG_FILE_EXTANSION = ".jpg";

class FileWorker {
public:
    static u_int64_t FileLenght(std::string&);

    static std::string GenerateFileName(std::string extansion = TXT_FILE_EXTENSION);
    static std::string GenerateFileName(int id, std::string extansion = TXT_FILE_EXTENSION);
};

} /* namespace utils */
} /* namespace ssodc */