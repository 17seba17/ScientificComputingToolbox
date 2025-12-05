#include "FunctionsArray.hpp"
#include "ButcherTableau.hpp"

#include <fstream>
#include <string>
#include <stdexcept> 

template <std::size_t size>
class ODE{
protected:
   const ButcherTableau bt_;
    const FunctionsArray<size>& fa_;  
    Eigen::VectorXd status_; 
   double time_;

    ODE(const ButcherTableau& bt, const FunctionsArray<size>& fa, Eigen::VectorXd status, double time) : bt_(bt), fa_(fa), status_(status), time_(time) {

 if (this->status_.size() != size) {
            throw std::invalid_argument("Initial status vector size does not match template size.");
        }

    }


void evolve(double dt){



    Eigen::MatrixXd M(size, bt_.size()); 
    for(int i=0;i<bt_.size();i++){

    double t2=time_+bt_.getC(i);
    Eigen::VectorXd now=status_;
    for(int j=0;j<i;j++){
auto bbb=M.col(j);


        now=now+dt*bt_.getA(j,i)*M.col(j);

    }

 auto a=fa_.functionResult(now,t2);

    M.col(i)=a;

    }

     status_+=dt*M*bt_.getB();
    time_+=dt;

}

public:

    void simulate(double dt, int num_steps, const std::string& output_filename)  {
        
        std::ofstream outfile(output_filename);
        if (!outfile.is_open()) {
            throw std::runtime_error("Errore: Impossibile aprire il file di output: " + output_filename);
        }

        outfile << "t";
        for (std::size_t i = 0; i < size; ++i) {
            outfile << ",x" << i;
        }
        outfile << "\n";

        
        outfile << time_;

        for (int i = 0; i < status_.size(); ++i) {
            outfile << "," << status_(i); 
        }
        outfile << "\n";


        for (int step = 0; step < num_steps; ++step) {
            
            evolve(dt);

            outfile << time_;

            for (int i = 0; i < status_.size(); ++i) {
                outfile << "," << status_(i);
            }
            outfile << "\n";
        }

    }



};

// Forward Euler, RK4, and (bonus) the explicit midpoint method.

template <std::size_t size>
class ForwardEuler : public ODE<size> { 
public:
    ForwardEuler(const FunctionsArray<size>& fa, const Eigen::VectorXd& status, double time) 
    : ODE<size>(ButcherTableau({}, std::vector<double>{1.0}), fa, status, time) {}
};


template <std::size_t size>
class RK4 : public ODE<size> {
public:
    RK4(const FunctionsArray<size>& fa, const Eigen::VectorXd& status,double time) 
    : ODE<size>(ButcherTableau({0.5,0,0.5,0,0,1},std::vector<double>{0.1666666,0.3333333,0.333333,0.1666666}),fa,status,time) {}
};

template <std::size_t size>
class Rule_3_8 : public ODE<size> { 
public:
    Rule_3_8(const FunctionsArray<size>& fa, const Eigen::VectorXd& status,double time) 
    : ODE<size>(ButcherTableau({0.3333333,-0.3333333,1,1,-1,1},std::vector<double>{0.125,0.375,0.375,0.125}),fa,status,time) {}
};

template <std::size_t size>
class SecondOrder : public ODE<size> { 
public:
    SecondOrder(const FunctionsArray<size>& fa, const Eigen::VectorXd& status, double time,double alpha) 
    : ODE<size>(ButcherTableau({alpha},std::vector<double>{1-1/(2*alpha),  1/(2*alpha)}),fa,status,time) {}
};

template <std::size_t size>
class Midpoint : public SecondOrder<size> { 
public:
    Midpoint(const FunctionsArray<size>& fa, const Eigen::VectorXd& status,double time) 
    : SecondOrder<size>(fa,status,time,0.5) {}
};

template <std::size_t size>
class Heun : public SecondOrder<size> { 
public:
    Heun(const FunctionsArray<size>& fa, const Eigen::VectorXd& status,double time) 
    : SecondOrder<size>(fa,status,time,1) {}
};

template <std::size_t size>
class Ralston : public SecondOrder<size> { 
public:
    Ralston(const FunctionsArray<size>& fa, const Eigen::VectorXd& status,double time) 
    : SecondOrder<size>(fa,status,time,0.666666) {}
};