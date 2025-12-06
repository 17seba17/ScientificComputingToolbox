// RawDataCSV.hpp
#ifndef RAWDATACSV_HPP
#define RAWDATACSV_HPP

#include "RawData.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace SCT {
namespace StatisticalAnalyses {

class RawDataCSV : public RawData {
public:
  RawDataCSV(std::string path) : RawData(path) { readTable(); }

  void readTable() override;

private:
  static std::vector<std::string> split(const std::string &line);
};

} // namespace StatisticalAnalyses
} // namespace SCT
#endif // RAWDATACSV_HPP