#include "RawDataCSV.hpp"
namespace SCT {
namespace StatisticalAnalyses {
void RawDataCSV::readTable() {
  std::ifstream csvFile(path_);
  if (!csvFile) {
    throw std::runtime_error("Impossible to open the file: " + path_);
  }

  std::string line;
  if (!std::getline(csvFile, line)) {
    throw std::runtime_error("Empty file: " + path_);
  }

  std::vector<std::string> headers = split(line);
  if (headers.empty()) {
    throw std::runtime_error("Empty header in file: " + path_);
  }

  const std::size_t ncols = headers.size();
  infoColumns_->clear();
  infoColumns_->reserve(ncols);
  rawdata_->clear();

  for (const auto &h : headers) {
    Detail::InfoColumn ic;
    ic.variable_ = h;
    ic.isCategorical_ = false;
    infoColumns_->push_back(std::move(ic));
  }

  std::vector<Detail::ExpectedType> colTypes(ncols, Detail::ExpectedType::Any);

  std::size_t lineNumber = 1;

  while (std::getline(csvFile, line)) {
    ++lineNumber;
    if (line.empty())
      continue;

    auto tokens = split(line);
    std::size_t originalCols = tokens.size();

    if (originalCols != ncols) {
      throw std::runtime_error("Row " + std::to_string(lineNumber) + " has " +
                               std::to_string(originalCols) +
                               " columns, but the header has " +
                               std::to_string(ncols));
    }

    for (std::size_t j = 0; j < ncols; ++j) {
      auto t = colTypes[j];
      auto value = getValue(tokens[j], t);
      colTypes[j] = t;
      rawdata_->push_back(std::move(value));
    }
  }

  const std::size_t nrows = (ncols == 0) ? 0 : rawdata_->size() / ncols;

  for (std::size_t j = 0; j < ncols; ++j) {
    Detail::InfoColumn &col = (*infoColumns_)[j];
    Detail::ExpectedType t = colTypes[j];
    col.isCategorical_ = (t == Detail::ExpectedType::String);

    if (!col.isCategorical_) {
      continue;
    }

    for (std::size_t i = 0; i < nrows; ++i) {
      const auto &cell = (*rawdata_)[i * ncols + j];
      if (!cell.has_value()) {
        continue;
      }
      if (std::holds_alternative<std::string>(*cell)) {
        const std::string &s = std::get<std::string>(*cell);
        if (col.labels_.find(s) == col.labels_.end()) {
          col.labels_.emplace(s, static_cast<int>(col.labels_.size()));
        }
      }
    }
  }
}

std::vector<std::string> RawDataCSV::split(const std::string &line) {
  // functions that splits a string when there is a comma
  std::vector<std::string> res;
  std::stringstream ss(line);
  std::string item;
  while (std::getline(ss, item, ',')) {
    res.push_back(item);
  }
  return res;
}

} // namespace StatisticalAnalyses
} // namespace SCT