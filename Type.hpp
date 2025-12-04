#ifndef TYPE_HPP
#define TYPE_HPP


#include<string>
#include<optional>
#include<variant>
#include <stdexcept>

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
#endif