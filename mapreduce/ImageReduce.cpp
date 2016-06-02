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
}

std::string ImageReduce::GetProcessedData() {
    return m_processedData;
}

} /* namespace mapreduce */
} /* namespace ssodc */