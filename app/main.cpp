//g++ main.cpp -o example     -I ./muparserx     -I ./eigen     -I /usr/local/boost_1_82_0/boost_1_89_0     -L ./muparserx/build     -lmuparserx     -std=c++17


#include <iostream>
#include <string>
#include <limits> 
#include "ODE.hpp"
#include "RawData.hpp"
#include "RawDataJSON.hpp"
#include "RawDataCSV.hpp"
#include "ProcessData.hpp"
#include "StatisticalAnalyses.hpp"
#include <filesystem>

int main(int argc, char* argv[]) {
    // Check for correct number of arguments

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file_path> <output_report_path>" << std::endl;
        return 1;
    }

    // Parse filenames from command line arguments
    const std::string inputPath = argv[1];
    const std::string outputPath = argv[2];

    try {
       
    std::filesystem::path p(inputPath);
    std::string ext = p.extension().string();

std::unique_ptr<RawData> rd;
 if(ext==".json")
 { 
    
    rd = std::make_unique<RawDataJSON>(inputPath);
 }
 else if(ext==".csv"){
        rd = std::make_unique<RawDataCSV>(inputPath);

 }

 else{
            throw std::runtime_error(ext + " è un formato non valido: usa file con estensione .csv o .json");
 }
ProcessedData pd(*rd);

 StatisticalAnalyses analyses(pd);
 
        analyses.generateReport(outputPath);

    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred during analysis: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
        return 1;
    }

    return 0;
}