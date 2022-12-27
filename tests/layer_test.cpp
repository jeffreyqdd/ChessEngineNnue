#define CATCH_CONFIG_MAIN
#include <Eigen/Dense>
#include "catch_amalgamated.hpp"
#include "../layers/linear.hpp"

using Eigen::Vector;
using Eigen::Matrix;

// ######### TEST CASES
TEST_CASE("LinearLayer is tested", "[linear]") {
  LinearLayer layer(3, 3, 1);

  Matrix<double, 3, 3> weights{
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };
  Vector<double, 3> bias{1, 2, 3};

  // check setters work
  SECTION("checking if input weights are valid"){
    Matrix<double, 3, 4> weights_bad1 {
      {1, 2, 3, 0},
      {4, 5, 6, 0},
      {7, 8, 9, 0},
    };
    Matrix<double, 4, 3> weights_bad2 {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9},
      {10, 11, 12}
    };
    Vector<double, 4> bias_bad1 {1, 2, 3, 4};

    REQUIRE_THROWS(layer.setWeights(weights_bad1));
    REQUIRE_THROWS(layer.setWeights(weights_bad2));
    REQUIRE_THROWS(layer.setBias(bias_bad1));

    REQUIRE_NOTHROW(layer.setWeights(weights));
    REQUIRE_NOTHROW(layer.setBias(bias));
  }

  // check forward
}
