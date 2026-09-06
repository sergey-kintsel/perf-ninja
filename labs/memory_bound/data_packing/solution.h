#include <vector>

// Assume those constants never change
constexpr int N = 1000000;
constexpr int minRandom = 0;
constexpr int maxRandom = 100;

// FIXME: this data structure can be reduced in size
// baseline 40 bytes:
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           21.7 ms         21.7 ms           27

// fixed alignment 24 bytes
// int i; // 4
// short s; // 2
// bool b; // 1
// long long l; // 8
// double d; // 8
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           9.16 ms         9.16 ms           81

// fixed sizes and alignment 16 bytes
// char i; // 1
// char s; // 1
// bool b; // 1
// short l; // 2
// double d; // 8
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           4.85 ms         4.85 ms          108

// using bitfields 8 bytes
// float d;         // 4
// unsigned l : 14;
// unsigned i : 7;
// unsigned s : 7;
// bool b : 1;
//
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           3.60 ms         3.60 ms          180
struct S {
  float d; // 4
  unsigned l : 14;
  unsigned i : 7;
  unsigned s : 7;
  bool b : 1;

  bool operator<(const S &s) const { return this->i < s.i; }
};

static_assert(sizeof(S) == 8, "Miracle didn't happen. Size is wrong");

void init(std::vector<S> &arr);
S create_entry(int first_value, int second_value);
void solution(std::vector<S> &arr);
