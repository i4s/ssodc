#include <ctime>
#include <fstream>
#include <algorithm>

#include "FileWorker.hpp"

namespace ssodc {
namespace utils {

u_int64_t FileWorker::FileLenght(std::string& fileName) {
    u_int64_t fileLenght;
    std::ifstream textFile(fileName.c_str(), std::ifstream::in);
    if (textFile.is_open()) {
        textFile.seekg(0, std::ios_base::end);
        fileLenght = textFile.tellg();
        textFile.close();
    }
    else {
        //TODO Errors
    }
    return fileLenght;
}

std::string FileWorker::GenerateFileName(std::string extansion) {
    std::time_t current = std::time(nullptr);
    std::string fileName(DIRECTORY_TO_SAVE);
    fileName.append(std::ctime(&current));
    std::replace(fileName.begin(), fileName.end(), ' ', '-');
    fileName.append(extansion);
    //fileName.insert(fileName.length() - 1, extansion);
    return fileName;
}

std::string FileWorker::GenerateFileName(int id, std::string extansion) {
    std::string fileName(DIRECTORY_TO_SAVE);
    fileName.append(std::to_string(id));
    fileName.append(extansion);
    return fileName;
}

} /* namespace utils */
} /* namespace ssodc */