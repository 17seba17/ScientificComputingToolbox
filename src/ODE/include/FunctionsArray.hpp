#ifndef FUNCTIONS_ARRAY_HPP
#define FUNCTIONS_ARRAY_HPP

#include <Eigen/Dense>
#include <array>
#include <parser/mpParser.h>
#include <string>

#include <memory>
namespace SCT {
namespace ODE {

template <std::size_t size> class FunctionsArray {

private:
  mutable std::array<mup::Value, size> values_;
  std::array<std::unique_ptr<mup::ParserX>, size> functions_;
  mutable mup::Value time_;

public:
  FunctionsArray(const std::array<std::string, size> &functions) {
    try {
      for (size_t i = 0; i < size; i++) {
        functions_[i] = std::make_unique<mup::ParserX>();

        for (size_t j = 0; j < size; j++) {
          std::string var = "x" + std::to_string(j);
          functions_[i]->DefineVar(var, mup::Variable(&values_[j]));
        }
        functions_[i]->DefineVar("t", &time_);
        functions_[i]->SetExpr(functions[i]);
      }
    } catch (const mup::ParserError &e) {
      std::cerr << "Errore di parsing (errore nella formula): " << e.GetMsg()
                << "\n";
      return;
    }
  }
  Eigen::VectorXd functionResult(const Eigen::VectorXd &input,
                                 double time) const {
    Eigen::VectorXd output(size);
    for (unsigned int i = 0; i < size; i++) {
      values_[i] = input(i);
    }
    time_ = time;
    for (unsigned int i = 0; i < size; i++) {

      mup::Value result = functions_[i]->Eval();

      if (result.IsScalar()) {

        output(i) = result.GetFloat();
      } else {
        std::cerr << result
                  << "Risultato non numerico o errore interno del parser."
                  << "\n";
      }
    }

    return output;
  }
};

} // namespace ODE
} // namespace SCT

#endif