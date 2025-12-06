#ifndef BUTCHER_TABLEAU_HPP
#define BUTCHER_TABLEAU_HPP

#include<vector>
#include<iostream>
#include <Eigen/Dense> 
namespace SCT{
namespace ODE{

class ButcherTableau{

 std::vector<double> a_;
 Eigen::VectorXd b_;
Eigen::VectorXd c_;
size_t size_;

void createC();

public:
    ButcherTableau(std::vector<double> a, Eigen::VectorXd b) : a_(std::move(a)), b_(std::move(b)) {
createC();
}

    ButcherTableau(std::vector<double> a, std::vector<double> b) : a_(std::move(a)) {
b_=Eigen::VectorXd(b.size());

for(int i=0;i<b.size();i++){

               

    b_(i)=b[i];
}
createC();
}

double getA(unsigned int i, unsigned int j)const{
if(i>=j){return 0.0;}
return a_[j*(j-1)/2+i];


}
double getB(unsigned int i)const{return b_(i);}
double getC(unsigned int i)const{return c_(i);}

Eigen::VectorXd getB()const{
    return b_;
}

size_t size()const{
    return size_;
}
};




}}//namespaces

#endif