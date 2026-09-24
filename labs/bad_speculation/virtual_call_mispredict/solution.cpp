#include "solution.h"

#include <random>

// baseline
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1            340 us          340 us         2041

// with sorted instances
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           85.8 us         85.6 us         7453

void generateObjects(InstanceArray &array) {
  std::default_random_engine generator(0);
  std::uniform_int_distribution<std::uint32_t> distribution(0, 2);

  InstanceArray bs;
  InstanceArray cs;

  for (std::size_t i = 0; i < N; i++) {
    const int value = distribution(generator);
    if (value == 0) {
      array.push_back(std::make_unique<ClassA>());
    } else if (value == 1) {
      bs.push_back(std::make_unique<ClassB>());
    } else {
      cs.push_back(std::make_unique<ClassC>());
    }
  }

  array.insert(array.end(), std::make_move_iterator(bs.begin()),
               std::make_move_iterator(bs.end()));
  array.insert(array.end(), std::make_move_iterator(cs.begin()),
               std::make_move_iterator(cs.end()));
}

// Invoke the `handle` method on all instances in `output`
void invoke(InstanceArray &array, std::size_t &data) {
  for (const auto &item : array) {
    item->handle(data);
  }
}
