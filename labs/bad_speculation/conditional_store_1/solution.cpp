
#include "solution.h"

// baseline
// ------------------------------------------------------------------
// Benchmark                        Time             CPU   Iterations
// ------------------------------------------------------------------
// bench1/iterations:10000        107 us          107 us        10000
//

// without conditions
// ------------------------------------------------------------------
// Benchmark                        Time             CPU   Iterations
// ------------------------------------------------------------------
// bench1/iterations:10000       22.8 us         22.8 us        10000

// Select items which have S.first in range [lower..upper]
std::size_t select(std::array<S, N> &output, const std::array<S, N> &input,
                   const std::uint32_t lower, const std::uint32_t upper) {
  std::size_t count = 0;
  for (const auto item : input) {
    output[count] = item;
    count += lower <= item.first && item.first <= upper;
  }
  return count;
}
