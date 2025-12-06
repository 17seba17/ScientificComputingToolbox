

#include "../src/ODE/include/ODE.hpp"
#include <filesystem>
#include <iostream>
#include <limits>
#include <string>

int main() {
  // Example from wiki
  std::cout << "let's solve dx/dt=tan(x)+1\n";
  Eigen::VectorXd input(1);
  input(0) = 1;

  SCT::ODE::FunctionsArray<1> functions({"tan(x0)+1"});

  SCT::ODE::Ralston<1> fe(functions, input, 1.0);
  std::string s = "example_from_wiki.txt";
  fe.simulate(0.025, 4, s);

  // Central force

  Eigen::VectorXd input2(2);
  input2(0) = 0;
  input2(1) = 1;

  SCT::ODE::FunctionsArray<2> functions2({"x1", "-x0"});

  SCT::ODE::RK4<2> fe2(functions2, input2, 0);
  std::string s2 = "central_force.txt";
  fe.simulate(0.0025, 3000, s2);

  return 0;
}