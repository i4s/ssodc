#ifndef SSODC_MAPREDUCE_MAP_HPP_
#define SSODC_MAPREDUCE_MAP_HPP_

#include <string>
#include <map>
#include <vector>
#include "../utils/TaskInfo.hpp"

namespace ssodc {
namespace mapreduce {

class map {
private:
	taskinfo m_taskInfo;
	//Contains id of free nodes and their power
	std::map<unsigned int, unsigned int> m_nodesPower;
	//Contains id of part of input data and id of nodes, where will be execute
	std::map<unsigned int, unsigned int> m_partOnNodes;
	//Contains id of part of input data and path to this part
	std::map<unsigned int, std::string> m_partPath;
	//Contains id of part of input data and coordinates to fold it
	std::map<unsigned int, std::vector<int> > m_partOfWhole;
public:
	map(taskinfo&);
	~map();

	int partitionData() = 0;
	int compileTaskSource();
	int setNodesPower(std::map<unsigned int, unsigned int>&);
	std::map<unsigned int, unsigned int>& getPartOnNodes();
	std::map<unsigned int, std::string>& getPartPath();
	std::map<unsigned int, std::vector<int> >& getPartOfWhole();
};
}
}

#endif //SSODC_MAPREDUCE_MAP_HPP_