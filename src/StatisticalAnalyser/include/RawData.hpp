#ifndef RAWDATA_HPP
#define RAWDATA_HPP

#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree.hpp"
#include "detail/InfoColumn.hpp"
#include "detail/Type.hpp"
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <variant>

namespace SCT {
namespace StatisticalAnalyses {

class RawData {
protected:
  using RawCells =
      std::vector<std::optional<std::variant<double, std::string>>>;
  std::string path_;
  // we use unique_ptr to perform std::move
  std::unique_ptr<std::vector<Detail::InfoColumn>> infoColumns_;
  std::unique_ptr<RawCells> rawdata_;

public:
  // constructor
  RawData(std::string path)
      : path_{path},
        infoColumns_(std::make_unique<std::vector<Detail::InfoColumn>>()),
        rawdata_(std::make_unique<RawCells>()) {}
  virtual ~RawData() = default;

  // std::move
  std::unique_ptr<std::vector<Detail::InfoColumn>> getInfoColumns() {
    return std::move(infoColumns_);
  }

  std::unique_ptr<RawCells> getRawData() { return std::move(rawdata_); }

  virtual void readTable() = 0; // we update rawdata_ and infoColumn_

  void print();
};

} // namespace StatisticalAnalyses
} // namespace SCT
#endif // RAWDATA_HPP