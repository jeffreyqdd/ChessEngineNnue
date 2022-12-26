//Half KP feature set stores a tuple of the following information:
// (king_square, piece_square, piece_type, piece_color) where piece_type != king
// 64 * 64 * 5 * 2 = 40960 total features
#pragma once
#include "board.hpp"

#define FEATURES 40960

struct NnueAccumulator {
  // two features one for each perspective
  float v[2][FEATURES];

  // returns the feature-set corresponding to the black/white perspective
  float* operator[](Color perspective);
};
