#ifndef SSODC_MAPREDUCE_MAPINTERFACE_HPP_
#define SSODC_MAPREDUCE_MAPINTERFACE_HPP_

namespace ssodc {
namespace mapreduce {

class MapInterface {
public:
    virtual int PartitionData() = 0;
    virtual int CompileTaskSource() = 0;
    virtual int GetNodesPower() = 0;
    virtual int SavePartOnNodes() = 0;
    virtual int SavePartPath() = 0;
    virtual int SavePartOfWhole() = 0;
};
}
}

#endif //SSODC_MAPREDUCE_MAPINTERFACE_HPP_