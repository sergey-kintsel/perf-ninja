#include "solution.hpp"

template <size_t N>
static std::array<std::size_t, N> createLookupTable() {
  std::array<std::size_t, N> arr;
  for (std::size_t i{}; i < N; ++i) {
    size_t x{};
    if (i < 13)
      x = 0;  //   13
    else if (i < 29)
      x = 1;  //   16
    else if (i < 41)
      x = 2;  //   12
    else if (i < 53)
      x = 3;  //   12
    else if (i < 71)
      x = 4;  //   18
    else if (i < 83)
      x = 5;  //   12
    else if (i < 100)
      x = 6;  //   17
    else {
      x = 7;
    }
    arr[i] = x;
  }
  return arr;
}

static auto lookupTable = createLookupTable<10000>();

static std::size_t mapToBucket(const std::size_t v) {
  return lookupTable[v];
}

std::array<std::size_t, NUM_BUCKETS> histogram(const std::vector<int> &values) {
  std::array<std::size_t, NUM_BUCKETS> retBuckets{0};
  for (auto v : values) {
    retBuckets[mapToBucket(v)]++;
  }
  return retBuckets;
}
