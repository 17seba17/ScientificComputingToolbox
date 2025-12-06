#ifndef STATISTICAL_ANALYSES_HPP
#define STATISTICAL_ANALYSES_HPP

#include "Iterator.hpp"
#include "ProcessedData.hpp"
#include <Eigen/Dense>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace SCT {
namespace StatisticalAnalyses {

class DataAnalyser {

private:
  using RawCells =
      std::vector<std::optional<std::variant<double, std::string>>>;

  const std::unique_ptr<std::vector<Detail::InfoColumn>> infoColumns_;
  const std::unique_ptr<Eigen::MatrixXd> processed_data;

public:
  DataAnalyser(ProcessedData &pd)
      : infoColumns_(pd.getInfoColumns()), processed_data(pd.getProcessData()) {
  }

  double calculateMean(int colIndex) const;
  double calculateVariance(int colIndex) const;
  double calculateStdDev(int colIndex) const;
  double calculateMedian(int colIndex) const;
  std::map<std::string, int> calculateFrequencyCount(int colIndex) const;
  std::string getClassificationReport(int colIndex) const;
  Eigen::MatrixXd calculateCorrelationMatrix() const;
  void generateReport(const std::string &filename) const;

  //// iterators

  RowView rows() const { return RowView{(*processed_data)}; }
  ColView cols() const { return ColView{(*processed_data)}; }
};

} // namespace StatisticalAnalyses
} // namespace SCT

#endif
