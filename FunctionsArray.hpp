#include <array>
#include <string>
#include <parser/mpParser.h> 
#include <Eigen/Dense>

template <std::size_t size>
class FunctionsArray {

private:

std::array<mup::Value, size> values_;
std::array<mup::ParserX, size> functions_;
mup::Value time_;
public:
double getTime()const{
    return time_.GetFloat();
}

    FunctionsArray(const std::array<std::string, size>& functions) 
    {
        try{
        for(size_t i=0;i<size;i++){
        for(size_t j=0;j<size;j++){
        std::string var="x"+std::to_string(j);
        functions_[i].DefineVar(var, Variable(&values_[j]));
        }
        functions_[i].DefineVar("t", &time);
        functions_[i].SetExpr(functions[i]);

        }
    }
    catch (const mup::ParserError &e) {
        std::cerr << "Errore di parsing (errore nella formula): " << e.GetMsg() << "\n";
        return ;
    }


    }

        Eigen::VectorXd functionResult(    Eigen::VectorXd& input, double time ){

            if(input.size()!=size){
                std::cerr<<"Dim non valide\n";
            }
                Eigen::VectorXd output(size); 
            for(int i=0;i<size;i++){
                values_[i]=input(i);
            }
            time_=time;

            for(int i=0;i<size;i++){

 try {
            mup::Value result = functions_[i].Eval(); 

            if (result.IsScalar()) {
               
                output(i)=result.GetFloat();
            } else {
                std::cerr << "Risultato non numerico o errore interno del parser." << "\n";
            }

        } catch (const mup::ParserError &e) {
            std::cerr << "Errore di esecuzione (es. divisione per zero): " << e.GetMsg() << "\n";
        }


            }


        }


};
