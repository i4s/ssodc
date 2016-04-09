#ifndef SSODC_MAPREDUCE_REDUCE_HPP_
#define SSODC_MAPREDUCE_REDUCE_HPP_

#include <string>
#include <map>
#include <vector>
#include "../utils/TaskInfo.hpp"

namespace ssodc {
namespace mapreduce {

class reduce {
private:
	taskinfo m_taskInfo;
	std::string m_solutionPath;
	//Contains id of part of input data and path to this part
	std::map<unsigned int, std::string> m_partPath;
	//Contains id of part of input data and coordinates to fold it
	std::map<unsigned int, std::vector<int> > m_partOfWhole;
public:
	reduce(taskinfo&);
	~reduce();

	int foldData() = 0;
	std::string getSolutionPath();
	int setPartPath(std::map<unsigned int, std::string>&);
	int setPartOfWhole(std::map<unsigned int, std::vector<int> >&);
};
}
}

#endif //SSODC_MAPREDUCE_REDUCE_HPP_