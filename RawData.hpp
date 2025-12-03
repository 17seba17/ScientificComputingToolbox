#ifndef RAWDATA_HPP
#define RAWDATA_HPP

#include <iostream>
#include <fstream>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include <string>
#include <variant>
#include <optional>
#include <unordered_map>
#include <iostream>
#include <variant>
#include <stdexcept>
#include <limits> 
#include <map>
#include <memory>
enum class ExpectedType { 
    Double, 
    String,
    Any
};

std::optional<std::variant<double, std::string>> getValue(const std::string& mystring, ExpectedType& type) {
 try {
    if(mystring=="NA"){type = ExpectedType::Any;return std::nullopt;}
        size_t pos = 0;
        double result = std::stod(mystring, &pos);
   
if (pos == mystring.length()) {//conversione perfetta
 if (type == ExpectedType::Double || type == ExpectedType::Any) {
                type = ExpectedType::Double;
                return result; 
            } else {
                return std::nullopt;
            }    
}

else {
            return std::nullopt;
        }

    }//try

    catch (const std::invalid_argument& e) {
        if (type == ExpectedType::String || type == ExpectedType::Any) {
            type = ExpectedType::String;
            return mystring;
        } else {
              type = ExpectedType::Any;
            return std::nullopt;
        }
    } // first catch

    catch (const std::out_of_range& e) {
        if (type == ExpectedType::String || type == ExpectedType::Any) {
            type = ExpectedType::String;
            return mystring;
        } else {
            type = ExpectedType::Any;
            return std::nullopt;
        }
    } // second catch

}


struct InfoColumn{
    std::unordered_map<std::string, int> labels_;
    std::string variable_;
    bool isCategorical_;
    
    void print()const{
 std::cout<<"Variabile: "<<variable_<<"\n";
 std::cout<<"Is categorical?: "<<isCategorical_<<"\n";
 if(isCategorical_)
{std::cout<<"Labels: ";
   for (auto const& [label, index] : labels_) { // Usa labelMap_
                std::cout << label << " -> " << index << ", ";
            }}
std::cout<<"\n\n";
    }
};


class RawData{
    protected:
    using RawCells=std::vector<std::optional<std::variant<double, std::string>>>;

std::unique_ptr<std::vector<InfoColumn>> infoColumns_;
std::unique_ptr<RawCells> rawdata_; //1000,34,NA,verde,NA,12000,24,136,rosso,donna...
std::string path_;


public:

RawData(std::string path) : path_{path}, infoColumns_(std::make_unique<std::vector<InfoColumn>>()), rawdata_(std::make_unique<RawCells>()) {
}


std::unique_ptr<std::vector<InfoColumn>> getInfoColumns() {
    return std::move(infoColumns_);
}

std::unique_ptr<RawCells> getRawData() {
    return std::move(rawdata_);
}

virtual void readTable ()=0; //aggiorno labels, variables, isCategorical e soprattutto rawdata


void print(){

    int rawdatasize=rawdata_->size();
    int infocolsize=infoColumns_->size();
if(infocolsize==0){
std::cerr<<rawdatasize<<"Il tuo dataframe non ha colonne";
}
    int observations=rawdatasize/infocolsize;

    for(int i=0;i<infoColumns_->size();i++){
        std::cout<<(*infoColumns_)[i].variable_<<",";
    }
std::cout<<"\n\n";
    for(int i=0;i< observations;i++){
    for(int j=0;j< infoColumns_->size();j++){
 if((*infoColumns_)[j].isCategorical_){
   std::cout<< std::get<std::string>((*rawdata_)[j+i*infoColumns_->size()].value_or("NA"))<<",";
 }
 else{
        double nan_value = std::numeric_limits<double>::quiet_NaN();
   std::cout<< std::get<double>((*rawdata_)[j+i*infoColumns_->size()].value_or(nan_value))<<",";

 }
    }
std::cout<<"\n";

    }
std::cout<<"\n";

}



};


#endif