#include "linear.hpp"
using namespace std;

using Eigen::MatrixXd;
using Eigen::VectorXd;

LinearLayer::LinearLayer(int input_size, int output_size, double lr) {
    if (input_size <= 0)
        throw std::invalid_argument("input_size needs to be greater than 0");
    if (output_size <= 0)
        throw std::invalid_argument("output size needs to be greater than 0");

    input_dim = input_size;
    output_dim = output_size;
    eta = lr;

    // floating point values are randomized between [-1, 1]
    //  so we need to adjust to [0, 1]
    weights = MatrixXd::Random(output_dim, input_dim);
    weights += MatrixXd::Constant(output_dim, input_dim, 1);
    weights /= 2;

    bias = VectorXd::Random(output_dim);
    bias += VectorXd::Constant(output_dim, 1);
    bias /= 2;
}

VectorXd LinearLayer::feedForward(const VectorXd &input) {
    if (input.size() != input_dim)
        throw std::invalid_argument("input dim does not match expected dim");

    input_val = input;  // TODO: ensure references does not create lifetime bugs
    output_val = weights * input + bias;
    return output_val;
}

VectorXd LinearLayer::backPropagate(const VectorXd &grad) {
    if (grad.size() != output_dim)
        throw std::invalid_argument("gradient dim does not match expected dim");

    // compute partial derivatives to be passed to previous layer
    VectorXd prev_layer_grad = weights.transpose() * grad;

    bias -= eta * grad;
    weights -= eta * (grad * input_val.transpose());  // outer product

    return prev_layer_grad;
}

void LinearLayer::setWeights(MatrixXd weights) {
    if (weights.rows() != output_dim || weights.cols() != input_dim)
        throw std::invalid_argument("new weights dimension does not match expected dimension");

    this->weights = weights;
}

void LinearLayer::setBias(VectorXd bias) {
    if (bias.size() != output_dim)
        throw std::invalid_argument("new bias dimension does not match expected dimension");

    this->bias = bias;
}

MatrixXd LinearLayer::getWeights() {
    return weights;
}

VectorXd LinearLayer::getBias() {
    return bias;
}