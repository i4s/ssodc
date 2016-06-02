#pragma once

#include "MapperInterface.hpp"

namespace ssodc {
namespace mapreduce {

class ImageMapper : public MapInterface {
    std::string m_filePath;
    std::map<int, std::string> m_partPath;
public:
    ImageMapper(std::string&);
    ~ImageMapper();

    int Mapping(int);
    std::map<int, std::string> GetPartPath();
};

} /* namespace mapreduce */
} /* namespace ssodc */