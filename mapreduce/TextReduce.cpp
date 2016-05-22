#include <ctime>
#include <string>
#include <fstream>
#include <algorithm>

#include "TextReduce.hpp"
#include "FileWorker.hpp"

namespace ssodc {
namespace mapreduce {

TextReduce::TextReduce(std::map<int, std::string>& path,
                       std::map<int, std::vector<int>>& coordinates) : m_partPath(path),
    m_partReduce(coordinates), m_processedData("") {
}

TextReduce::~TextReduce() {
}

int TextReduce::Reducing() {
    std::string m_processedData = ssodc::utils::FileWorker::GenerateFileName();
    std::ofstream outputFile(m_processedData.c_str(), std::ofstream::out);
    if (!outputFile.is_open()) {
        //TODO ERR
        return -1;
    }
    auto coordinates = m_partReduce.begin();
    for (auto path = m_partPath.begin(); path != m_partPath.end();
            path++, coordinates++) {
        u_int64_t fileLength = ssodc::utils::FileWorker::FileLenght(path->second);
        std::ifstream inputPartFile(path->second, std::ifstream::in);
        if(!inputPartFile.is_open()) {
            //ERR
            outputFile.close();
            return -1;
        }
        for(u_int64_t i = 0; i < fileLength; i++) {
            char symbol;
            inputPartFile >> symbol;
            outputFile << symbol;
        }
        inputPartFile.close();
    }
    outputFile.close();
    return 0;
}

std::string TextReduce::GetProcessedData() {
    return m_processedData;
}

} /* namespace mapreduce */
} /* namespace ssodc */