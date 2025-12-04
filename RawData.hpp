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
#include "Type.hpp"
#include "InfoColumn.hpp"




class RawData{
    protected:
    using RawCells=std::vector<std::optional<std::variant<double, std::string>>>;

std::unique_ptr<std::vector<InfoColumn>> infoColumns_;
std::unique_ptr<RawCells> rawdata_; //1000,34,NA,verde,NA,12000,24,136,rosso,donna...
std::string path_;


public:

RawData(std::string path) : path_{path}, infoColumns_(std::make_unique<std::vector<InfoColumn>>()), rawdata_(std::make_unique<RawCells>()) {
}
virtual ~RawData() = default;


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