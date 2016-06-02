#include <ctime>
#include <string>
#include <fstream>
#include <algorithm>

#include "CImg.h"
#include "ImageReduce.hpp"
#include "FileWorker.hpp"

namespace ssodc {
namespace mapreduce {

ImageReduce::ImageReduce(std::map<int, std::string>& path) : m_partPath(path) {
    m_processedData = "";
}

ImageReduce::~ImageReduce() {
}

int ImageReduce::Reducing() {
    std::string m_processedData = ssodc::utils::FileWorker::GenerateFileName(
        ssodc::utils::BMP_FILE_EXTANSION);
    cimg_library::CImg<unsigned char> resultImage;
    for (auto path = m_partPath.begin(); path != m_partPath.end();
            path++) {
        cimg_library::CImg<unsigned char> part(path->second.c_str());
        resultImage.append(part, 'y');
    }
    resultImage.save(m_processedData.c_str());
    return 0;
    /*
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
    return 0;*/
}

std::string ImageReduce::GetProcessedData() {
    return m_processedData;
}

} /* namespace mapreduce */
} /* namespace ssodc */