// int main(){
//     std::optional<std::variant<int, std::string>> cell{9};

//     std::cout<<std::get<int>(cell.value_or("NA"))<<"\n";
//     return 0;
// }


#include <iostream>
 #include <fstream>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include <string>
#include <variant>
#include <optional>
 #include <Eigen/Dense>
#include<variant>
 using Column = std::variant<Eigen::VectorXd, Eigen::VectorXi>;
class ReadTable{

std::string path_;

std::vector<Column> dataframe_;
std::vector<std::string> variables_; 
std::vector<bool> isCategorical_;
std::vector<std::vector<std::string>> labels_; 

ReadTable(std::string& path): path_{path} {};

 std::vector<Column> getDataframe() const {
    return dataframe_;
 }
 Column getColumn(unsigned int index){
    return dataframe_[index];
}


bool isCategorical(int index){
    return isCategorical_[index];
}


std::vector<std::string> getVariabes(){
    return variables_;
}; 


std::vector<std::vector<std::string>>  getLabels(){
    return labels_;
}

 virtual void readTable()=0;

};

class ReadTableJSON : public ReadTable{
    using boost::property_tree::ptree;

void ReadTable ()override{
    return;
}

};








int main() {

    std::ifstream jsonFile("input.txt");

    ptree pt;
    read_json(jsonFile, pt);

    for (auto & array_element: pt) {
        for (auto & property: array_element.second) {
            std::cout << property.first << " = " << property.second.get_value < std::string > () << "\n";
        }
    }
}
