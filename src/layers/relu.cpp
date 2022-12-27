#include <cassert>
#include "relu.hpp"
#include <Eigen/Dense>

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;

VectorXd Relu::feedForward(const VectorXd &input){
  output_val = VectorXd::Constant(input.size(), 0);
  output_val = output_val.cwiseMax(input);
  return output_val;
}

VectorXd Relu::backPropagate(VectorXd grad){
  assert(grad.size() == output_val.size());
  grad.unaryExpr([](double x){
    if (x > 0) return 1;
    return 0;
  });
  return grad;
}

VectorXd ClippedRelu::feedForward(const VectorXd &input){
  output_val = Relu::output_val;
  output_val = Relu::feedForward(input);
  output_val = output_val.cwiseMin(VectorXd::Constant(input.size(), 1));
  return output_val;
}

VectorXd ClippedRelu::backPropagate(VectorXd grad){
  grad = Relu::backPropagate(grad);
  grad.unaryExpr([](double x){
    if (x > 1) return (double) 0;
    return x;
  });
  return grad;
}
