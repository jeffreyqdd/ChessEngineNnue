#include "nnue.hpp"
#include "board.hpp"

float* NnueAccumulator::operator[](Color perspective) {
  return v[perspective];
}

void refresh_accumulator(){

}
