
#include "solution.h"
#include <algorithm>
#include <stdlib.h>

// baseline
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1            611 us          611 us          964

// with lambda
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1            308 us          308 us         2170

static int compare(const void *lhs, const void *rhs) {
  auto &a = *reinterpret_cast<const S *>(lhs);
  auto &b = *reinterpret_cast<const S *>(rhs);

  if (a.key1 < b.key1)
    return -1;

  if (a.key1 > b.key1)
    return 1;

  if (a.key2 < b.key2)
    return -1;

  if (a.key2 > b.key2)
    return 1;

  return 0;
}

void solution(std::array<S, N> &arr) {
  std::ranges::sort(arr, [](const S& a, const S& b) {
    return a.key1 == b.key1 ? a.key2 < b.key2 : a.key1 < b.key1;
  });
}
