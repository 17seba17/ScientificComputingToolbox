#ifndef BUTCHER_TABLEAU_HPP
#define BUTCHER_TABLEAU_HPP

#include <Eigen/Dense>
#include <iostream>
#include <vector>
namespace SCT {
namespace ODE {

class ButcherTableau {

  std::vector<double> a_;
  Eigen::VectorXd b_;
  Eigen::VectorXd c_;
  size_t size_;

  void createC();

public:
  ButcherTableau(std::vector<double> a, Eigen::VectorXd b);
  ButcherTableau(std::vector<double> a, std::vector<double> b);

  double getA(unsigned int i, unsigned int j) const;
  double getB(unsigned int i) const;
  double getC(unsigned int i) const;
  Eigen::VectorXd getB() const;
  size_t size() const;
};

} // namespace ODE
} // namespace SCT

#endif