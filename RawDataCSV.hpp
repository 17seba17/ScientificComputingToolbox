// RawDataCSV.hpp
#ifndef RAWDATACSV_HPP
#define RAWDATACSV_HPP

#include "RawData.hpp"
#include "Types.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

class RawDataCSV : public RawData {
public:
    using RawData::RawData; // eredita il costruttore RawData(path)

    void readTable() override {
        std::ifstream csvFile(path_);
        if (!csvFile) {
            throw std::runtime_error("Impossibile aprire file: " + path_);
        }

        std::string line;
        if (!std::getline(csvFile, line)) {
            throw std::runtime_error("File vuoto: " + path_);
        }

        // 1) Header -> nomi colonne
        std::vector<std::string> headers = split(line);
        if (headers.empty()) {
            throw std::runtime_error("Header vuoto in file: " + path_);
        }

        const std::size_t ncols = headers.size();
        infoColumns_->clear();
        infoColumns_->reserve(ncols);
        rawdata_->clear();

        for (const auto& h : headers) {
            InfoColumn ic;
            ic.variable_ = h;
            ic.isCategorical_ = false; // lo decideremo dopo
            infoColumns_->push_back(std::move(ic));
        }

        // tipo "aggregato" di ogni colonna
        std::vector<ExpectedType> colTypes(ncols, ExpectedType::Any);

        std::size_t lineNumber = 1; // abbiamo già letto l'header

        // 2) Leggo tutte le righe e accumulo i valori in rawdata_
        while (std::getline(csvFile, line)) {
            ++lineNumber;
            if (line.empty()) continue;

            auto tokens = split(line);
            std::size_t originalCols = tokens.size();

            // controllo formato righe
            if (originalCols != ncols) {
                throw std::runtime_error(
                    "Riga " + std::to_string(lineNumber) +
                    " ha " + std::to_string(originalCols) +
                    " colonne, ma l'header ne ha " + std::to_string(ncols));
            }

            for (std::size_t j = 0; j < ncols; ++j) {
                auto t = colTypes[j];
                auto value = getValue(tokens[j], t); // aggiorna t
                colTypes[j] = t;
                rawdata_->push_back(std::move(value));
            }
        }

        const std::size_t nrows =
            (ncols == 0) ? 0 : rawdata_->size() / ncols;

        // 3) Finalizzo InfoColumn (isCategorical_ + labels_ per stringhe)
        for (std::size_t j = 0; j < ncols; ++j) {
            InfoColumn& col = (*infoColumns_)[j];
            ExpectedType t = colTypes[j];
            col.isCategorical_ = (t == ExpectedType::String);

            if (!col.isCategorical_) {
                continue;
            }

            for (std::size_t i = 0; i < nrows; ++i) {
                const auto& cell = (*rawdata_)[i * ncols + j];
                if (!cell.has_value()) {
                    continue;
                }
                if (std::holds_alternative<std::string>(*cell)) {
                    const std::string& s = std::get<std::string>(*cell);
                    if (col.labels_.find(s) == col.labels_.end()) {
                        col.labels_.emplace(
                            s,
                            static_cast<int>(col.labels_.size())
                        );
                    }
                }
            }
        }

        // 4) Stampa di base (come nel JSON) per debug
        for (const auto& col : *infoColumns_) {
            col.print();
        }
    }

private:
    static std::vector<std::string> split(const std::string& line) {
        std::vector<std::string> res;
        std::stringstream ss(line);
        std::string item;
        while (std::getline(ss, item, ',')) {
            res.push_back(item);
        }
        return res;
    }
};

#endif // RAWDATACSV_HPP