#ifndef RAWDATAJSON_HPP
#define RAWDATAJSON_HPP
#include "RawData.hpp"

class RawDataJSON : public RawData{
    public:
    RawDataJSON(std::string path) : RawData(path) {readTable();}
    
    void  readTable () override{



//apertura per lettura file e creazione albero
 std::ifstream jsonFile(path_);
    using boost::property_tree::ptree;
    ptree pt;
    read_json(jsonFile, pt);

    // ricerca variabili
std::unordered_map<std::string, InfoColumn> myvar;

    for (auto & array_element: pt) {
        for (auto & property: array_element.second) {
auto type= ExpectedType::Any;
auto value= getValue(property.second.data(), type);
if(type!=ExpectedType::Any)
{
    InfoColumn ic;
    
double categorical=(type==ExpectedType::String)?true:false;

ic.isCategorical_=categorical;
ic.variable_=property.first;

  auto [it, inserted] = myvar.emplace(property.first, std::move(ic)); 

if(type==ExpectedType::String){  
    InfoColumn& info = it->second; 
    info.labels_.emplace(property.second.data(), info.labels_.size());

            }

        }//any

    
        }}//i due for


    for (auto const& pair : myvar) {
    infoColumns_->push_back(pair.second); 
    }
///Reading all values


for (auto & array_element: pt) {
for(auto const& column : (*infoColumns_)){
   
    auto type= column.isCategorical_ ? ExpectedType::String : ExpectedType::Double;

    auto it = std::find_if(
    array_element.second.begin(), 
    array_element.second.end(),
    [&column](auto const& property) {
        return property.first == column.variable_;
    }
);

if (it == array_element.second.end()) {
     rawdata_->push_back(std::nullopt);
}
else {
    rawdata_->push_back(getValue(it->second.data(), type));
}
    

}}/// i due for

// for(auto const& element : (*infoColumns_)){
//     element.print();
// }
    
}//read Table



};



#endif