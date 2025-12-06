#ifndef   PROCESSDATA_HPP
#define   PROCESSDATA_HPP

#include <iostream>
#include <string>
#include <variant>
#include <optional>
#include <Eigen/Dense>
#include <iostream>
#include <variant>
#include <optional>
#include <stdexcept>
#include <limits> 
#include <map>
#include <memory>


namespace SCT{
namespace StatisticalAnalyses{

double mostFrequent(const std::vector<double>& vec) {

    std::unordered_map<double, int> conteggi;
    
    for (double numero : vec) {
        conteggi[numero]++;
    }

    double moda = vec[0];
    int max_frequenza = 0;

    for (const auto& pair : conteggi) {
        double numero = pair.first;
        int frequenza = pair.second;

        if (frequenza > max_frequenza) {
            max_frequenza = frequenza;
            moda = numero;
        }
    }

    return moda;
}


class ProcessedData{
using RawCells=std::vector<std::optional<std::variant<double, std::string>>>;
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


ProcessedData(RawData& rd) : infoColumns_(rd.getInfoColumns()), rawdata_(rd.getRawData()), processed_data( std::make_unique<Eigen::MatrixXd>()) {
// ProcessedData(RawData& rd) : infoColumns_() {
     processData();
}

private:
void processData(){


    std::vector<double> mostFrequentVec;
    std::vector<double> means;
    std::vector<bool> areThereNans;
    int rawdatasize=rawdata_->size();
    int infocolsize=infoColumns_->size();
if(infocolsize==0){
std::cerr<<rawdatasize<<"Il tuo dataframe non ha colonne";
}
    int observations=rawdatasize/infocolsize;

    for(int i=0;i<infoColumns_->size();i++){

    int NANs=0;
    double reduced_sum=0.0;
    std::vector<double> vec;
    areThereNans.push_back(false);

    bool isCategorical=(*infoColumns_)[i].isCategorical_;

        for(int j=i;j<rawdatasize;j+=infocolsize){
        auto  thiscell=(*rawdata_)[j];

        
        if(isCategorical){

            if(thiscell==std::nullopt) {areThereNans.back()=true;}

                            try {

    auto index = (*infoColumns_)[i].labels_.at(std::get<std::string>(thiscell.value_or("NA"))); 
    vec.push_back(index);
} catch (const std::out_of_range& e) {
    areThereNans.back()=true;

}
catch(...){std::cerr<<"error caught";areThereNans.back()=true;}


     }///if categorical
     else{
                            if(thiscell==std::nullopt) {NANs++;areThereNans.back()=true;}
                            else{
                                        double nan_value = std::numeric_limits<double>::quiet_NaN();
                                        double value=std::get<double>(thiscell.value_or(nan_value));
                                        if(value==nan_value){NANs++;}
                                        else{reduced_sum+=value/observations;}

                            }

     } //if numerical




                    }//second for

                    
                      if(isCategorical){
                       
                            if(vec.size()==0){
                                std::cerr<<"problema!";
                            }
                        mostFrequentVec.push_back(mostFrequent(vec));
                    }
                    else{
                    means.push_back(reduced_sum/(observations-NANs)*observations);
                    }
                    
    }///first for

//                 ////creation of EigenMatrix
          
    (processed_data)->resize(observations, infocolsize);
    int mean_idx = 0;
    int freq_idx = 0;
    double nan_value = std::numeric_limits<double>::quiet_NaN();

    for(int i=0;i<infoColumns_->size();i++){
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
        for(int j_raw = i; j_raw < rawdata_->size(); j_raw += (infoColumns_->size()), r++){
            auto thiscell = (*rawdata_)[j_raw];
            double final_value = nan_value;

            if (isCategorical) {
                if (thiscell == std::nullopt) {
                    final_value = imputation_value;
                } else {
                    try {
                        final_value = (*infoColumns_)[i].labels_.at(std::get<std::string>(thiscell.value_or("NA")));
                    } catch (const std::out_of_range& e) {
                        final_value =  imputation_value;
                    } catch (...) {
                        final_value = imputation_value;
                    }
                }
            } else {
                if (thiscell == std::nullopt) {
                    final_value =imputation_value;
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



};

}}//namespaces

#endif