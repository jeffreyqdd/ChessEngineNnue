#pragma once
#include <Eigen/Dense>
using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;

// In a linear layer, we take our input vector x and multiply it with
// a matrix A of weights: Ax = b where b is the resulting output vector
// thus, the dims of matrix A are OUTPUT_DIMSxINPUT_DIMS in row-column

class LinearLayer {
private:
  MatrixXd weights;
  VectorXd bias, input_val, output_val;
  int output_dim;
  int input_dim;
  double eta; // learning rate
public:
  LinearLayer();
  LinearLayer(int input_size, int output_size, double lr);
  VectorXd feedForward(const VectorXd &input);
  VectorXd backPropagate(const VectorXd &grad);
};
