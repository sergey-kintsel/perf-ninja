#include "solution.hpp"
#include <array>
#include <iostream>
#include <print>

unsigned getSumOfDigits(unsigned n) {
  unsigned sum = 0;
  while (n != 0) {
    sum = sum + n % 10;
    n = n / 10;
  }
  return sum;
}

// baseline
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           56.6 ms         56.6 ms           11

// split into two parallel checks
// while (l2) {
// if (i < len - SIZE) {
//   i += 2;
//   unsigned a = (l2++)->value;
//   unsigned b = (l2++)->value;
//   if (a == v || b == v) {
//     retVal += getSumOfDigits(v);
//     break;
//   }
// } else {
//   if (l2->value == v) {
//     retVal += getSumOfDigits(v);
//     break;
//   }
//   l2 = l2->next;
// }
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           14.6 ms         14.6 ms           39

// with 3
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           12.2 ms         12.2 ms           48

// with 4
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           11.1 ms         11.1 ms           57

// with array of Size 4
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           11.0 ms         11.0 ms           58

// higher size it just degrades


// with proper bucketing and size = 8
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           12.6 ms         12.6 ms           49

// Task: lookup all the values from l2 in l1.
// For every found value, find the sum of its digits.
// Return the sum of all digits in every found number.
// Both lists have no duplicates and elements placed in *random* order.
// Do NOT sort any of the lists. Do NOT store elements in a hash_map/sets.

// Hint: Traversing a linked list is a long data dependency chain:
//       to get the node N+1 you need to retrieve the node N first.
//       Think how you can execute multiple dependency chains in parallel.
constexpr size_t SIZE = 4;
unsigned solution(List *l1, List *l2) {
  unsigned retVal = 0;

  List *head2 = l2;

  // O(N^2) algorithm:
  while (l1) {
    std::array<unsigned, SIZE> values;
    size_t len{};
    while (l1 && len < SIZE) {
      values[len++] = l1->value;
      l1 = l1->next;
    }

    l2 = head2;
    size_t found{};
    while (l2 && found < len) {
      for (size_t j{}; j < len; ++j) {
        if (l2->value == values[j]) {
          ++found;
          retVal += getSumOfDigits(values[j]);
          break;
        }
      }
      l2 = l2->next;
    }
  }

  return retVal;
}
