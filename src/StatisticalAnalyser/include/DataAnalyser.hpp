#ifndef STATISTICAL_ANALYSES_HPP
#define STATISTICAL_ANALYSES_HPP

#include <iostream>
#include <vector>
#include <string>
#include <variant>
#include <optional>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <map>
#include <Eigen/Dense>
 #include "Iterator.hpp"
#include "ProcessData.hpp"


namespace SCT{
namespace StatisticalAnalyses{

class DataAnalyser {
public:

private:
    using RawCells = std::vector<std::optional<std::variant<double, std::string>>>;
    

    const std::unique_ptr<std::vector<Detail::InfoColumn>> infoColumns_;
    const std::unique_ptr<Eigen::MatrixXd> processed_data;

public:
    DataAnalyser(ProcessedData &pd) : infoColumns_(pd.getInfoColumns()), processed_data(pd.getProcessData())  {
    }


    // 1. Mean (Column-wise)
    double calculateMean(int colIndex) const {
        if (processed_data->rows() == 0) return 0.0;
        return processed_data->col(colIndex).mean();
    }

    // 2. Variance (Sample Variance)
    double calculateVariance(int colIndex) const {
        if (processed_data->rows() < 2) return 0.0;
        
        double mean = calculateMean(colIndex);
        double sum_sq_diff = 0.0;
        
        for(int i = 0; i < processed_data->rows(); ++i) {
            double val = (*processed_data)(i, colIndex);
            sum_sq_diff += (val - mean) * (val - mean);
        }
        
        return sum_sq_diff / (processed_data->rows() - 1);
    }

    // 3. Standard Deviation
    double calculateStdDev(int colIndex) const {
        return std::sqrt(calculateVariance(colIndex));
    }

    // 4. Median
    double calculateMedian(int colIndex) const {
        int n = processed_data->rows();
        if (n == 0) return 0.0;

        // Copy column to vector to sort
        std::vector<double> v(n);
        Eigen::VectorXd col = processed_data->col(colIndex);
        Eigen::Map<Eigen::VectorXd>(v.data(), n) = col;

        std::sort(v.begin(), v.end());

        if (n % 2 == 0) {
            return (v[n / 2 - 1] + v[n / 2]) / 2.0;
        } else {
            return v[n / 2];
        }
    }

    // 5. Frequency Count / Classification
    // Returns a map of Label Name -> Count
    std::map<std::string, int> calculateFrequencyCount(int colIndex) const {
        std::map<std::string, int> freqMap;
        
        // Safety check
        if (colIndex < 0 || colIndex >= infoColumns_->size()) return freqMap;
        
        const auto& info = (*infoColumns_)[colIndex];

        // Create a reverse map (int -> string) for lookup
        std::unordered_map<int, std::string> intToLabel;
        if (info.isCategorical_) {
            for (const auto& pair : info.labels_) {
                intToLabel[pair.second] = pair.first;
            }
        }

        for (int i = 0; i < processed_data->rows(); ++i) {
            double val = (*processed_data)(i, colIndex);
            
            std::string key;
            if (info.isCategorical_) {
                int intVal = static_cast<int>(val);
                if (intToLabel.count(intVal)) {
                    key = intToLabel[intVal];
                } else {
                    key = "Unknown (" + std::to_string(intVal) + ")";
                }
            } else {
                // For numerical data, we might treat the number as a bucket/label
                key = std::to_string(val);
            }
            freqMap[key]++;
        }
        return freqMap;
    }

    // 6. Classification Analysis
    // Usually implies class distribution for target variables
    std::string getClassificationReport(int colIndex) const {
        auto freqs = calculateFrequencyCount(colIndex);
        std::stringstream ss;
        ss << "Class Distribution for " << (*infoColumns_)[colIndex].variable_ << ":\n";
        int total = processed_data->rows();
        
        for (const auto& pair : freqs) {
            double percentage = (double)pair.second / total * 100.0;
            ss << "  - " << pair.first << ": " << pair.second 
               << " (" << std::fixed << std::setprecision(2) << percentage << "%)\n";
        }
        return ss.str();
    }

    // 7. Correlation Analysis (Matrix)
    Eigen::MatrixXd calculateCorrelationMatrix() const {
        if (processed_data->rows() < 2) return Eigen::MatrixXd();

        // Center the data (subtract mean)
        Eigen::MatrixXd centered = processed_data->rowwise() - processed_data->colwise().mean();
        
        // Calculate Covariance Matrix: (X^T * X) / (n-1)
        Eigen::MatrixXd cov = (centered.adjoint() * centered) / double(processed_data->rows() - 1);

        // Convert Covariance to Correlation
        Eigen::MatrixXd corr(cov.rows(), cov.cols());
        
        for (int i = 0; i < cov.rows(); ++i) {
            for (int j = 0; j < cov.cols(); ++j) {
                double stdDevI = std::sqrt(cov(i, i));
                double stdDevJ = std::sqrt(cov(j, j));
                
                if (stdDevI > 0 && stdDevJ > 0) {
                    corr(i, j) = cov(i, j) / (stdDevI * stdDevJ);
                } else {
                    corr(i, j) = 0.0; // Handle constant columns
                }
            }
        }
        return corr;
    }

    // --- Report Generator ---

    // Function to create or overwrite file with all analyses
    void generateReport(const std::string& filename) const {
        std::ofstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
            return;
        }

        file << "=================================================\n";
        file << "            STATISTICAL ANALYSES REPORT          \n";
        file << "=================================================\n\n";

        int numCols = processed_data->cols();

        // 1. Per Variable Analysis
        for (int i = 0; i < numCols; ++i) {
            const auto& info = (*infoColumns_)[i];
            
            file << "VARIABLE: " << info.variable_ 
                 << " [" << (info.isCategorical_ ? "Categorical" : "Numerical") << "]\n";
            file << "-------------------------------------------------\n";

            if (info.isCategorical_) {
                // Categorical Analysis: Counts and Percentages
                file << getClassificationReport(i);
            } else {
                // Numerical Analysis: Mean, Median, StdDev
                file << "  Mean:     " << calculateMean(i) << "\n";
                file << "  Median:   " << calculateMedian(i) << "\n";
                file << "  Variance: " << calculateVariance(i) << "\n";
                file << "  Std Dev:  " << calculateStdDev(i) << "\n";
            }
            file << "\n";
        }

        // 2. Correlation Analysis (Matrix)
        file << "=================================================\n";
        file << "               CORRELATION MATRIX                \n";
        file << "=================================================\n\n";

        // Print Header
        file << std::setw(12) << " ";
        for (int i = 0; i < numCols; ++i) {
            // Truncate name if too long for cleaner table
            std::string name = (*infoColumns_)[i].variable_;
            if(name.length() > 10) name = name.substr(0, 10);
            file << std::setw(12) << name;
        }
        file << "\n";

        Eigen::MatrixXd corrMat = calculateCorrelationMatrix();

        for (int i = 0; i < corrMat.rows(); ++i) {
            std::string name = (*infoColumns_)[i].variable_;
            if(name.length() > 10) name = name.substr(0, 10);
            file << std::setw(12) << name;

            for (int j = 0; j < corrMat.cols(); ++j) {
                file << std::setw(12) << std::fixed << std::setprecision(4) << corrMat(i, j);
            }
            file << "\n";
        }

        file.close();
        std::cout << "Report successfully generated: " << filename << std::endl;
    }


   //// iterator in our data


    RowView rows() const {
        return RowView{(*processed_data)};
    }
    ColView cols() const {
        return ColView{(*processed_data)};
    }
};


}}//namespaces

#endif 
