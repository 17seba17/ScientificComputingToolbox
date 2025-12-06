#include "RawData.hpp"
namespace SCT {
namespace StatisticalAnalyses {

void RawData::print() {

  int rawdatasize = rawdata_->size();
  int infocolsize = infoColumns_->size();
  if (infocolsize == 0) {

    throw std::runtime_error("The number is column is zero!");
  }
  int observations = rawdatasize / infocolsize;

  for (unsigned int i = 0; i < infoColumns_->size(); i++) {
    std::cout << (*infoColumns_)[i].variable_ << ",";
  }
  std::cout << "\n\n";
  for (int i = 0; i < observations; i++) {
    for (unsigned int j = 0; j < infoColumns_->size(); j++) {
      if ((*infoColumns_)[j].isCategorical_) {
        std::cout << std::get<std::string>(
                         (*rawdata_)[j + i * infoColumns_->size()].value_or(
                             "NA"))
                  << ",";
      } else {
        double nan_value = std::numeric_limits<double>::quiet_NaN();
        std::cout << std::get<double>(
                         (*rawdata_)[j + i * infoColumns_->size()].value_or(
                             nan_value))
                  << ",";
      }
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

} // namespace StatisticalAnalyses
} // namespace SCT