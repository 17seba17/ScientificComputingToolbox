#include "ProcessedData.hpp"

namespace SCT {
namespace StatisticalAnalyses {

void ProcessedData::processData() {

  std::vector<double> mostFrequentVec;
  std::vector<double> means;
  std::vector<bool> areThereNans;
  int rawdatasize = rawdata_->size();
  int infocolsize = infoColumns_->size();
  if (infocolsize == 0) {
    throw std::runtime_error("Your dataframe doesn't have columns!");
  }
  int observations = rawdatasize / infocolsize;

  for (int i = 0; i < infoColumns_->size(); i++) {

    int NANs = 0;
    double reduced_sum = 0.0;
    std::vector<double> vec;
    areThereNans.push_back(false);

    bool isCategorical = (*infoColumns_)[i].isCategorical_;

    for (int j = i; j < rawdatasize; j += infocolsize) {
      auto thiscell = (*rawdata_)[j];

      if (isCategorical) {

        if (thiscell == std::nullopt) {
          areThereNans.back() = true;
        }

        try {

          auto index = (*infoColumns_)[i].labels_.at(
              std::get<std::string>(thiscell.value_or("NA")));
          vec.push_back(index);
        } catch (const std::out_of_range &e) {
          areThereNans.back() = true;

        } catch (...) {
          std::cerr << "error caught";
          areThereNans.back() = true;
        }

      } /// if categorical
      else {
        if (thiscell == std::nullopt) {
          NANs++;
          areThereNans.back() = true;
        } else {
          double nan_value = std::numeric_limits<double>::quiet_NaN();
          double value = std::get<double>(thiscell.value_or(nan_value));
          if (value == nan_value) {
            NANs++;
          } else {
            reduced_sum += value / observations;
          }
        }

      } // if numerical

    } // second for

    if (isCategorical) {

      if (vec.size() == 0) {
        throw std::runtime_error(
            "The vector must have size different from zero\n");
      }
      mostFrequentVec.push_back(mostFrequent(vec));
    } else {
      means.push_back(reduced_sum / (observations - NANs) * observations);
    }

  } /// first for

  //////creation of EigenMatrix

  (processed_data)->resize(observations, infocolsize);
  int mean_idx = 0;
  int freq_idx = 0;
  double nan_value = std::numeric_limits<double>::quiet_NaN();

  for (int i = 0; i < infoColumns_->size(); i++) {
    bool isCategorical = (*infoColumns_)[i].isCategorical_;
    bool impute = areThereNans[i];
    double imputation_value;

    if (isCategorical) {
      imputation_value = mostFrequentVec[freq_idx];
      freq_idx++;
    } else {
      imputation_value = means[mean_idx];
      mean_idx++;
    }

    int r = 0;
    for (int j_raw = i; j_raw < rawdata_->size();
         j_raw += (infoColumns_->size()), r++) {
      auto thiscell = (*rawdata_)[j_raw];
      double final_value = nan_value;

      if (isCategorical) {
        if (thiscell == std::nullopt) {
          final_value = imputation_value;
        } else {
          try {
            final_value = (*infoColumns_)[i].labels_.at(
                std::get<std::string>(thiscell.value_or("NA")));
          } catch (const std::out_of_range &e) {
            final_value = imputation_value;
          } catch (...) {
            final_value = imputation_value;
          }
        }
      } else {
        if (thiscell == std::nullopt) {
          final_value = imputation_value;
        } else {
          double value = std::get<double>(thiscell.value_or(nan_value));
          if (value == nan_value) {
            final_value = imputation_value;
          } else {
            final_value = value;
          }
        }
      }

      (*processed_data)(r, i) = final_value;
    }
  }
}

} // namespace StatisticalAnalyses
} // namespace SCT