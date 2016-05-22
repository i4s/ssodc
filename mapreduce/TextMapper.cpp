#include <string>
#include <thread>
#include <vector>
#include <future>
#include <fstream>
#include <iostream>
#include <functional>

#include "TextMapper.hpp"
#include "FileWorker.hpp"

namespace ssodc {
namespace mapreduce {

TextMapper::TextMapper(std::string& filePath) : m_filePath(filePath) {
}

TextMapper::~TextMapper() {
}

int TextMapper::Mapping(int numberOfParts) {
	u_int64_t fileLenght = ssodc::utils::FileWorker::FileLenght(m_filePath);
	u_int64_t partLenght = fileLenght / numberOfParts;
	std::ifstream fileToMap(m_filePath.c_str(), std::ifstream::in);
    if (!fileToMap.is_open()) {
    	//TODO ERR
    	return -1;
    }
	for (int i = 0; i < numberOfParts - 1; i++) {
        std::string partFileName = ssodc::utils::FileWorker::GenerateFileName(i + 1);
        std::ofstream newPart(partFileName.c_str(), std::ofstream::out);
        if(!newPart.is_open()) {
        	//TODO ERR
        	fileToMap.close();
        	return -1;
        }
        for(u_int64_t j = 0; j < partLenght; j++) {
        	char symbol;
        	fileToMap >> symbol;
        	newPart << symbol;
        }
        newPart.close();
        std::vector<int> coordinate;
        coordinate.push_back(i + 1);
        m_partPath.insert(std::pair<int, std::string>(i + 1, partFileName));
        m_partReduce.insert(std::pair<int, std::vector<int>>(i + 1, coordinate));
        m_partReduce[i + 1].push_back(i + 1);
	}
	std::string fileName = ssodc::utils::FileWorker::GenerateFileName(numberOfParts);
    std::ofstream newPart(fileName.c_str(), std::ofstream::out);
    if(!newPart.is_open()) {
        //TODO ERR
        fileToMap.close();
    }
    for(u_int64_t j = 0; j < (partLenght + fileLenght - partLenght * numberOfParts); j++) {
    	char symbol;
      	fileToMap >> symbol;
    	newPart << symbol;
    }
    std::vector<int> coordinate;
    coordinate.push_back(numberOfParts);
    m_partPath.insert(std::pair<int, std::string>(numberOfParts, fileName));
    m_partReduce.insert(std::pair<int, std::vector<int>>(numberOfParts, coordinate));
    m_partReduce[numberOfParts].push_back(numberOfParts);
    fileToMap.close();
    newPart.close();
    return 0;
}

std::map<int, std::string> TextMapper::GetPartPath() {
	return m_partPath;
}

std::map<int, std::vector<int>> TextMapper::GetPartReduce() {
	return m_partReduce;
}

} /* namespace mapreduce */
} /* namespace ssodc */