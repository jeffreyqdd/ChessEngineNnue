#pragma once
#include <Eigen/Dense>
using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;

class Relu{
protected:
  VectorXd output_val;
public:
  Relu();
  VectorXd feedForward(const VectorXd &input);
  VectorXd backPropagate(VectorXd grad);
};

class ClippedRelu : private Relu {
public:
  ClippedRelu();
  VectorXd feedForward(const VectorXd &input);
  VectorXd backPropagate(VectorXd grad);
};
