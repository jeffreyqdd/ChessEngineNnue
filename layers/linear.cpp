#include <cassert>
#include "linear.hpp"
#include <Eigen/Dense>

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;

LinearLayer::LinearLayer(int input_size, int output_size, double lr){
  assert(input_size > 0);
  assert(output_size > 0);

  input_dim = input_size;
  output_dim = output_size;
  eta = lr;

  // floating point values are randomized between [-1, 1]
  //  so we need to adjust to [0, 1]
  weights = MatrixXd::Random(output_dim, input_dim) ;
  weights += MatrixXd::Constant(output_dim, input_dim, 1);
  weights /= 2;

  bias = VectorXd::Random(output_dim);
  bias += VectorXd::Constant(output_dim, 1);
  bias /= 2;
}

VectorXd LinearLayer::feedForward(const VectorXd &input){
    assert(input.size() == input_dim);
    input_val = input; //TODO: ensure references does not create lifetime bugs
    output_val = weights * input + bias;
    return output_val;
}

VectorXd LinearLayer::backPropagate(const VectorXd &grad){
  assert(grad.size() == output_dim);
  // compute partial derivatives to be passed to previous layer
  VectorXd prev_layer_grad = weights.transpose() * grad;

  bias -= eta * grad;

  return prev_layer_grad;
}

int main() {
  return 0;
}
