#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "linear.hpp"

using Eigen::Matrix;
using Eigen::Vector;

// ######### TEST CASES
TEST_CASE("LinearLayer is tested", "[linear]") {
    LinearLayer layer(3, 3, 1.0);

    Matrix<double, 3, 3> weights{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    Vector<double, 3> bias{1, 2, 3};

    SECTION("check if constructor works") {
        MatrixXd layer_weights = layer.getWeights();
        VectorXd layer_bias = layer.getBias();

        for (int i = 0; i < 3; i++) {
            CHECK((layer_bias(i) >= 0 && layer_bias(i) <= 1));
            for (int j = 0; j < 3; j++) {
                CHECK((layer_weights(i, j) >= 0 && layer_weights(i, j) <= 1));
            }
        }
    }
    SECTION("checking if input weights/biases are valid") {
        Matrix<double, 3, 4> weights_bad1{
            {1, 2, 3, 0},
            {4, 5, 6, 0},
            {7, 8, 9, 0},
        };
        Matrix<double, 4, 3> weights_bad2{
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
            {10, 11, 12}};
        Vector<double, 4> bias_bad1{1, 2, 3, 4};

        REQUIRE_THROWS(layer.setWeights(weights_bad1));
        REQUIRE_THROWS(layer.setWeights(weights_bad2));
        REQUIRE_THROWS(layer.setBias(bias_bad1));

        REQUIRE_NOTHROW(layer.setWeights(weights));
        REQUIRE_NOTHROW(layer.setBias(bias));
    }

    SECTION("check forward calculation") {
        layer.setWeights(weights);
        layer.setBias(bias);
        Vector<double, 3> inputs{0, 1, 2};

        VectorXd results = layer.feedForward(inputs);
        Vector<double, 3> answer{9, 19, 29};

        REQUIRE(results == answer);
    }

    SECTION("check back propagation") {
        Vector<double, 3> inputs{0, 1, 2};
        Vector<double, 3> actual{8, 21, 2};

        Vector<double, 3> results = layer.feedForward(inputs);
        Vector<double, 3> gradient = layer.backPropagate(actual);
    }
}
