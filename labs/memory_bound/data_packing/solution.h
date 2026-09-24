#include <vector>

// Assume those constants never change
constexpr int N = 1000000;
constexpr int minRandom = 0;
constexpr int maxRandom = 100;

// baseline
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           22.1 ms         22.1 ms           28

// with bitfields
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           3.61 ms         3.61 ms          195

struct S {
  unsigned i:7;
  unsigned s:7;
  unsigned l:14;
  bool b:1;
  float d;

  bool operator<(const S &_s) const { return this->i < _s.i; }
};

static_assert(sizeof(S) == 8, "S is too big");

void init(std::vector<S> &arr);
S create_entry(int first_value, int second_value);
void solution(std::vector<S> &arr);
