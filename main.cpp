
#include "ODE.hpp"

#include <filesystem>

int main() {
  //                     Eigen::VectorXd input(1);
  //                     input(0)=1;

  // SCT::ODE::FunctionsArray<1> functions({"tan(x0)+1"}); // Oggetto 1

  // SCT::ODE::Ralston<1> fe(functions, input, 1.0);
  //       std::string s="ode.txt";
  //        fe.simulate(0.025,4,s);

  Eigen::VectorXd input(2);
  input(0) = 0;
  input(1) = 1;

  SCT::ODE::FunctionsArray<2> functions({"x1", "-x0"}); // Oggetto 1

  SCT::ODE::Ralston<2> fe(functions, input, 0);
  std::string s = "ode.txt";
  fe.simulate(0.0025, 3000, s);
}