
#include "benchmark/benchmark.h"
#include "solution.h"
#include <memory>

static void bench1(benchmark::State &state) {
  std::unique_ptr<Matrix> a(new Matrix());
  init(*a);

  std::unique_ptr<Matrix> b(new Matrix());
  zero(*b);

  for (auto _ : state) {
    *b = power(*a, 2021);
    benchmark::DoNotOptimize(b);
  }
}

// Register the function as a benchmark
BENCHMARK(bench1)->Iterations(10);

// baseline
// ---------------------------------------------------------------
// Benchmark                     Time             CPU   Iterations
// ---------------------------------------------------------------
// bench1/iterations:10  453680208 ns    453605586 ns           10

// if doesn't touch res[i][j] on each iteration
// ---------------------------------------------------------------
// Benchmark                     Time             CPU   Iterations
// ---------------------------------------------------------------
// bench1/iterations:10  227535514 ns    227492183 ns           10

// Run the benchmark
BENCHMARK_MAIN();
