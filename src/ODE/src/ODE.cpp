#include "ODE.hpp"

namespace SCT {
namespace ODE {

template <std::size_t size>
ODE::ODE(const ButcherTableau &bt, const FunctionsArray<size> &fa,
         Eigen::VectorXd status, double time)
    : bt_(bt), fa_(fa), status_(status), time_(time) {

  if (this->status_.size() != size) {
    throw std::invalid_argument(
        "Initial status vector size does not match template size.");
  }
}

template <std::size_t size> void ODE::evolve(double dt) {

  Eigen::MatrixXd M(size, bt_.size());
  for (int i = 0; i < bt_.size(); i++) {

    double t2 = time_ + bt_.getC(i);
    Eigen::VectorXd now = status_;
    for (int j = 0; j < i; j++) {
      auto bbb = M.col(j);

      now = now + dt * bt_.getA(j, i) * M.col(j);
    }

    auto a = fa_.functionResult(now, t2);

    M.col(i) = a;
  }

  status_ += dt * M * bt_.getB();
  time_ += dt;
}

template <std::size_t size>
void ODE::simulate(double dt, int num_steps,
                   const std::string &output_filename) {

  std::ofstream outfile(output_filename);
  if (!outfile.is_open()) {
    throw std::runtime_error("Errore: Impossibile aprire il file di output: " +
                             output_filename);
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

} // namespace ODE
} // namespace SCT