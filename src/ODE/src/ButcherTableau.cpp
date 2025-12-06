#include "../include/ButcherTableau.hpp"
#include <cmath>
namespace SCT {
namespace ODE {

void ButcherTableau::createC() {

  int S_a = a_.size();
  int S_b = b_.size();
  if ((S_b - 1) * S_b / 2 != S_a) {
    std::cerr << "errore di compatibilità\n";
  }
  size_ = S_b;
  c_.resize(S_b);
  c_(0) = 0.0;

  int count = 1;
  double check = 0.0;
  for (int i = 0; i < S_b - 1; i++) {
    check += b_(i);

    double sum = 0.0;
    for (int j = 0; j < count; j++) {
      sum += (a_[count * (count - 1) / 2 + j]);
    }
    count++;
    c_(i) = sum;
  }
  check += b_(S_b - 1);
  if (std::abs(check - 1.0) > 0.0001) {
    throw std::runtime_error("The Butcher Tableaus is not consistent");
  }

  if (c_.size() != b_.size()) {
    throw std::runtime_error("Error during creation of C");
  }
} // creating C

ButcherTableau::ButcherTableau(std::vector<double> a, Eigen::VectorXd b)
    : a_(std::move(a)), b_(std::move(b)) {
  createC();
}

ButcherTableau::ButcherTableau(std::vector<double> a, std::vector<double> b)
    : a_(std::move(a)) {
  b_ = Eigen::VectorXd(b.size());
  for (unsigned int i = 0; i < b.size(); i++) {
    b_(i) = b[i];
  }
  createC();
}

double ButcherTableau::getA(unsigned int i, unsigned int j) const {
  if (i >= j) {
    return 0.0;
  }
  return a_[j * (j - 1) / 2 + i];
}
double ButcherTableau::getB(unsigned int i) const { return b_(i); }
double ButcherTableau::getC(unsigned int i) const { return c_(i); }

Eigen::VectorXd ButcherTableau::getB() const { return b_; }

size_t ButcherTableau::size() const { return size_; }

} // namespace ODE
} // namespace SCT