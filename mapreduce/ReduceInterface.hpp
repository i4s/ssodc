#ifndef SSODC_MAPREDUCE_REDUCEINTERFACE_HPP_
#define SSODC_MAPREDUCE_REDUCEINTERFACE_HPP_

namespace ssodc {
namespace mapreduce {

class ReduceInterface {
public:
    virtual int FoldData() = 0;
    virtual int SendSolutionPath() = 0;
    virtual int LoadPartPath() = 0;
    virtual int LoadPartOfWhole() = 0;
};
}
}

#endif //SSODC_MAPREDUCE_REDUCEINTERFACE_HPP_