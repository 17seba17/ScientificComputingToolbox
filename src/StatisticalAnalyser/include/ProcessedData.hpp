#ifndef PROCESSDATA_HPP
#define PROCESSDATA_HPP

#include "RawData.hpp"
#include "detail/InfoColumn.hpp"
#include <Eigen/Dense>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <variant>

namespace SCT {
namespace StatisticalAnalyses {

inline double mostFrequent(const std::vector<double> &vec) {

  std::unordered_map<double, int> conteggi;

  for (double numero : vec) {
    conteggi[numero]++;
  }

  double moda = vec[0];
  int max_frequenza = 0;

  for (const auto &pair : conteggi) {
    double numero = pair.first;
    int frequenza = pair.second;

    if (frequenza > max_frequenza) {
      max_frequenza = frequenza;
      moda = numero;
    }
  }

  return moda;
}

class ProcessedData {
  using RawCells =
      std::vector<std::optional<std::variant<double, std::string>>>;
  std::unique_ptr<std::vector<Detail::InfoColumn>> infoColumns_;
  std::unique_ptr<RawCells> rawdata_;
  std::unique_ptr<Eigen::MatrixXd> processed_data;

public:
  std::unique_ptr<std::vector<Detail::InfoColumn>> getInfoColumns() {
    return std::move(infoColumns_);
  }

  std::unique_ptr<Eigen::MatrixXd> getProcessData() {
    return std::move(processed_data);
  }

  ProcessedData(RawData &rd)
      : infoColumns_(rd.getInfoColumns()), rawdata_(rd.getRawData()),
        processed_data(std::make_unique<Eigen::MatrixXd>()) {
    processData();
  }

private:
  void processData();
};

} // namespace StatisticalAnalyses
} // namespace SCT

#endif