

#include <iostream>
#include <string>
#include <limits> 
#include "../src/ODE/include/ODE.hpp"
// #include "../src/ODE/include/RawData.hpp"
// #include "../src/ODE/include/RawDataJSON.hpp"
// #include "../src/ODE/include/RawDataCSV.hpp"
// #include "../src/ODE/include/ProcessData.hpp"
// #include "../src/ODE/include/DataAnalyser.hpp"
#include <filesystem>

// int main(int argc, char* argv[]) {
//     // Check for correct number of arguments

//     if (argc != 3) {
//         std::cerr << "Usage: " << argv[0] << " <input_file_path> <output_report_path>" << std::endl;
//         return 1;
//     }

//     // Parse filenames from command line arguments
//     const std::string inputPath = argv[1];
//     const std::string outputPath = argv[2];

//     try {
       
//     std::filesystem::path p(inputPath);
//     std::string ext = p.extension().string();

// std::unique_ptr<SCT::StatisticalAnalyses::RawData> rd;
//  if(ext==".json")
//  { 
    
//     rd = std::make_unique<SCT::StatisticalAnalyses::RawDataJSON>(inputPath);
//  }
//  else if(ext==".csv"){
//         rd = std::make_unique<SCT::StatisticalAnalyses::RawDataCSV>(inputPath);

//  }

//  else{
//             throw std::runtime_error(ext + " è un formato non valido: usa file con estensione .csv o .json");
//  }

//  SCT::StatisticalAnalyses::ProcessedData pd(*rd);

//  SCT::StatisticalAnalyses::DataAnalyser analyses(pd);
 
//         analyses.generateReport(outputPath);

//     } catch (const std::exception& e) {
//         std::cerr << "An unexpected error occurred during analysis: " << e.what() << std::endl;
//         return 1;
//     } catch (...) {
//         std::cerr << "An unknown error occurred." << std::endl;
//         return 1;
//     }

//     return 0;
// }

int main(){
//                     Eigen::VectorXd input(1);
//                     input(0)=1;

// SCT::ODE::FunctionsArray<1> functions({"tan(x0)+1"}); // Oggetto 1



// SCT::ODE::Ralston<1> fe(functions, input, 1.0); 
//       std::string s="ode.txt";
//        fe.simulate(0.025,4,s);




//                            Eigen::VectorXd input(2);
//                     input(0)=0;
//                     input(1)=1;

// SCT::ODE::FunctionsArray<2> functions({"x1","-x0"}); // Oggetto 1

// SCT::ODE::Ralston<2> fe(functions, input, 0); 
//       std::string s="ode.txt";
//        fe.simulate(0.0025,3000,s);

return 0;
    
}