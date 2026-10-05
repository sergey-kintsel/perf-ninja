#include "solution.hpp"

// baseline
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           23.1 us         23.1 us        29343

// vectorized
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1          0.001 us        0.001 us    761603519

uint16_t checksum(const Blob &blob) {
  uint16_t acc = 0;
  for (const auto value : blob) {
    acc += value + acc < value;
  }
  return acc;
}
