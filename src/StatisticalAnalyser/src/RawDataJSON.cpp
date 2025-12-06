#include "RawDataJSON.hpp"
namespace SCT{
namespace StatisticalAnalyses{


    void  RawDataJSON::readTable () {



//apertura per lettura file e creazione albero
 std::ifstream jsonFile(path_);
    using boost::property_tree::ptree;
    ptree pt;
    read_json(jsonFile, pt);

    // ricerca variabili
std::unordered_map<std::string, Detail::InfoColumn> myvar;

    for (auto & array_element: pt) {
        for (auto & property: array_element.second) {
auto type= Detail::ExpectedType::Any;
auto value= getValue(property.second.data(), type);
if(type!=Detail::ExpectedType::Any)
{
    Detail::InfoColumn ic;
    
double categorical=(type==Detail::ExpectedType::String)?true:false;

ic.isCategorical_=categorical;
ic.variable_=property.first;

  auto [it, inserted] = myvar.emplace(property.first, std::move(ic)); 

if(type==Detail::ExpectedType::String){  
    Detail::InfoColumn& info = it->second; 
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
   
    auto type= column.isCategorical_ ? Detail::ExpectedType::String : Detail::ExpectedType::Double;

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


}}