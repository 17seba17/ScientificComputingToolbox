
#include "../src/StatisticalAnalyser/include/DataAnalyser.hpp"
#include "../src/StatisticalAnalyser/include/RawData.hpp"
#include "../src/StatisticalAnalyser/include/RawDataCSV.hpp"
#include "../src/StatisticalAnalyser/include/RawDataJSON.hpp"
#include <filesystem>

int main(int argc, char *argv[]) {

  if (argc != 3) {
    std::cerr << "Usage: " << argv[0]
              << " <input_file_path> <output_report_path>\n";
    return 1;
  }

  const std::string inputPath = argv[1];
  const std::string outputPath = argv[2];

  try {

    std::filesystem::path p(inputPath);
    std::string ext = p.extension().string();

    std::unique_ptr<SCT::StatisticalAnalyses::RawData> rd;
    if (ext == ".json") {

      rd = std::make_unique<SCT::StatisticalAnalyses::RawDataJSON>(inputPath);
    } else if (ext == ".csv") {
      rd = std::make_unique<SCT::StatisticalAnalyses::RawDataCSV>(inputPath);

    }

    else {
      throw std::runtime_error(
          ext +
          " è un formato non valido: usa file con estensione .csv o .json");
    }

    SCT::StatisticalAnalyses::ProcessedData pd(*rd);

    SCT::StatisticalAnalyses::DataAnalyser analyses(pd);

    analyses.generateReport(outputPath);

  } catch (const std::exception &e) {
    std::cerr << "An unexpected error occurred during analysis: " << e.what()
              << "\n";
    return 1;
  } catch (...) {
    std::cerr << "An unknown error occurred.\n";
    return 1;
  }

  return 0;
}