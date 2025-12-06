#ifndef RAWDATAJSON_HPP
#define RAWDATAJSON_HPP
#include "RawData.hpp"

namespace SCT{
namespace StatisticalAnalyses{

    
class RawDataJSON : public RawData{
    public:
    RawDataJSON(std::string path) : RawData(path) {readTable();}
    
    void  readTable () override;



};


}}//namespaces
#endif