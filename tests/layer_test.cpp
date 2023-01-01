#include <fmt/core.h>

#include <iostream>

#include "catch_amalgamated.hpp"
#include "linear.hpp"
#include "relu.hpp"

#define CATCH_CONFIG_MAIN

using Eigen::Matrix;
using Eigen::Vector;

// ######### TEST CASES
TEST_CASE("Relu tests", "[relu]") {
}

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

    SECTION("check forward and backward") {
        layer.setWeights(weights);
        layer.setBias(bias);
        Vector<double, 3> inputs{0, 1, 2};
        Vector<double, 3> answer{9, 19, 29};
        Vector<double, 3> actual{8, 21, 2};

        // check if prediction steps works
        VectorXd results = layer.feedForward(inputs);
        REQUIRE(results == answer);

        // back propagate w/ the real answer and check calculated gradient
        //  and resulting weights/biases
        Vector<double, 3> gradient = layer.backPropagate(actual - answer);
        REQUIRE(gradient == Vector<double, 3>{-182, -208, -234});
        REQUIRE(
            layer.getWeights() == Matrix<double, 3, 3>{
                                      {1, 3, 5},
                                      {4, 3, 2},
                                      {7, 35, 63}});
        REQUIRE(layer.getBias() == Vector<double, 3>{2, 0, 30});
    }

    SECTION("Performance Benchmarks") {
        for (int i = 0, dims = 1; i < 3; i++) {
            dims *= 10;
            BENCHMARK_ADVANCED(fmt::format("{:d}x{:d} dimension", dims, dims))
            (Catch::Benchmark::Chronometer meter) {
                int numRows = dims, numCols = dims;
                MatrixXd matrix = MatrixXd::Random(numRows, numCols);
                VectorXd vector = VectorXd::Random(numCols);

                meter.measure([matrix, vector] { return matrix * vector; });
            };
        }
    }
}