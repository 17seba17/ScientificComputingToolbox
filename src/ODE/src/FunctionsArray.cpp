#include "FunctionsArray.hpp"

namespace SCT {
namespace ODE {

template <std::size_t size>
FunctionsArray::FunctionsArray(const std::array<std::string, size> &functions) {
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
    std::cerr << "Parsing error (error in the formula): " << e.GetMsg() << "\n";
    return;
  }
}

template <std::size_t size>
Eigen::VectorXd FunctionsArray::functionResult(const Eigen::VectorXd &input,
                                               double time) const {
  Eigen::VectorXd output(size);
  for (int i = 0; i < size; i++) {
    values_[i] = input(i);
  }
  time_ = time;
  for (int i = 0; i < size; i++) {

    mup::Value result = functions_[i]->Eval();

    if (result.IsScalar()) {

      output(i) = result.GetFloat();
    } else {
      std::cerr << result
                << "Non numeric result or internal error during parsing.\n";
    }
  }

  return output;
}

} // namespace ODE
} // namespace SCT