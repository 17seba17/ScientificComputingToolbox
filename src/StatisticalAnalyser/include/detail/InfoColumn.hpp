#ifndef INFOCOLUMN_HPP
#define INFOCOLUMN_HPP

#include <iostream>
#include <string>
#include <unordered_map>

namespace SCT {
namespace StatisticalAnalyses {
namespace Detail {

struct InfoColumn {
  std::unordered_map<std::string, int> labels_;
  std::string variable_;
  bool isCategorical_;

  void print() const {
    std::cout << "Variabile: " << variable_ << "\n";
    std::cout << "Is categorical?: " << isCategorical_ << "\n";
    if (isCategorical_) {
      std::cout << "Labels: ";
      for (auto const &[label, index] : labels_) {
        std::cout << label << " -> " << index << ", ";
      }
    }
    std::cout << "\n\n";
  }
};
} // namespace Detail
} // namespace StatisticalAnalyses
} // namespace SCT

#endif // INFOCOLUMN_HPP