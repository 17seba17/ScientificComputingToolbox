#include "FunctionsArray.hpp"
#include "ButcherTableau.hpp"
template <std::size_t size>
class ODE{

   const ButcherTableau bt_;
   const FunctionsArray<size> fa_;
   Eigen::VectorXd status_; 

    ODE(ButcherTableau& bt, FunctionsArray<size>& fa, Eigen::VectorXd status) : bt_(bt), fa_(fa), status_(status) {
    }


void evolve(double dt){
    Eigen::MatrixXd M(size, size); 

    for(int i=0;i<size;i++){

    double t2=fa_.getTime()+bt_.getC(i);
    Eigen::VectorXd now=status_;
    for(int j=0;j<i;j++){
        now=now+dt*bt_.getA(j,i)*M.col(j);
    
    }

    M.col(i)=fa_.functionResult(t2, now);

    }

    status_+=dt*M*bt_.getB();


}



};

// Forward Euler, RK4, and (bonus) the explicit midpoint method.


template <std::size_t size>
class ForwardEuler : public ODE<size> { 
public:
    ForwardEuler(const FunctionsArray<size>& fa, const Eigen::VectorXd& status) 
    : ODE<size>(ButcherTableau({},{1.0}),fa,status) {}
};


template <std::size_t size>
class RK4 : public ODE<size> {
public:
    RK4(const FunctionsArray<size>& fa, const Eigen::VectorXd& status) 
    : ODE<size>(ButcherTableau({0.5,0,0.5,0,0,1},{1/6,1/3,1/3,1/6}),fa,status) {}
};

template <std::size_t size>
class Rule_3_8 : public ODE<size> { 
public:
    Rule_3_8(const FunctionsArray<size>& fa, const Eigen::VectorXd& status) 
    : ODE<size>(ButcherTableau({1/3,-1/3,1,1,-1,1},{1/8,3/8,3/8,1/8}),fa,status) {}
};

template <std::size_t size>
class SecondOrder : public ODE<size> { 
public:
    SecondOrder(const FunctionsArray<size>& fa, const Eigen::VectorXd& status, double alpha) 
    : ODE<size>(ButcherTableau({alpha},{1-1/(2*alpha),  1/(2*alpha)}),fa,status) {}
};

template <std::size_t size>
class Midpoint : public SecondOrder<size> { 
public:
    Midpoint(const FunctionsArray<size>& fa, const Eigen::VectorXd& status) 
    : SecondOrder<size>(fa,status,0.5) {}
};

template <std::size_t size>
class Heun : public SecondOrder<size> { 
public:
    Heun(const FunctionsArray<size>& fa, const Eigen::VectorXd& status) 
    : SecondOrder<size>(fa,status,1) {}
};

template <std::size_t size>
class Ralston : public SecondOrder<size> { 
public:
    Ralston(const FunctionsArray<size>& fa, const Eigen::VectorXd& status) 
    : SecondOrder<size>(fa,status,2/3) {}
};