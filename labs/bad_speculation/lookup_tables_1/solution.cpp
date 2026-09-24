#include "solution.hpp"

// baseline
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           3425 us         3415 us          195


// with compile-time calculated buckets
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1            485 us          485 us         1463

constexpr static std::size_t mapToBucket(const std::size_t v) {
  //   size of a bucket
  if (v < 13)
    return 0; //   13
  if (v < 29)
    return 1; //   16
  if (v < 41)
    return 2; //   12
  if (v < 53)
    return 3; //   12
  if (v < 71)
    return 4; //   18
  if (v < 83)
    return 5; //   12
  if (v < 100)
    return 6; //   17
  return DEFAULT_BUCKET;
}

constinit static std::array<std::size_t, 10000> MAPPING = []() {
  std::array<std::size_t, 10000> res;
  for (std::size_t i{}; i < 10000; ++i) {
    res[i] = mapToBucket(i);
  }
  return res;
}();

std::array<std::size_t, NUM_BUCKETS> histogram(const std::vector<int> &values) {
  std::array<std::size_t, NUM_BUCKETS> retBuckets{0};
  for (const auto v : values) {
    retBuckets[MAPPING[v]]++;
  }
  return retBuckets;
}
