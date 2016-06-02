#include <string>
#include <thread>
#include <vector>
#include <future>
#include <fstream>
#include <iostream>
#include <functional>

#include "CImg.h"
#include "FileWorker.hpp"
#include "ImageMapper.hpp"

namespace ssodc {
namespace mapreduce {

ImageMapper::ImageMapper(std::string& filePath) : m_filePath(filePath){
	m_partPath = std::map<int, std::string>();
}

ImageMapper::~ImageMapper() {
}

int ImageMapper::Mapping(int numberOfParts) {
    cimg_library::CImg<unsigned char> image(m_filePath.c_str());
    u_int64_t fullHeight = image.height();
    u_int64_t height = image.height() / numberOfParts;
    u_int64_t width = image.width();
    for(int i = 0; i < numberOfParts - 1; i++) {
        std::string partFileName = ssodc::utils::FileWorker::GenerateFileName(i + 1,
            ssodc::utils::BMP_FILE_EXTANSION);
        cimg_library::CImg<unsigned char> part =
            image.get_crop(0, i * height, width - 1, (i + 1) * height - 1);
            part.save(partFileName.c_str());
        m_partPath.insert(std::pair<int, std::string>(i + 1, partFileName));
    }
    std::string partFileName = ssodc::utils::FileWorker::GenerateFileName(numberOfParts,
        ssodc::utils::BMP_FILE_EXTANSION);
    cimg_library::CImg<unsigned char> part =
        image.get_crop(0, height * (numberOfParts - 1), width - 1, fullHeight - 1);
    m_partPath.insert(std::pair<int, std::string>(numberOfParts, partFileName));
    part.save(partFileName.c_str());
    return 0;
}

std::map<int, std::string> ImageMapper::GetPartPath() {
    return m_partPath;
}

} /* namespace mapreduce */
} /* namespace ssodc */