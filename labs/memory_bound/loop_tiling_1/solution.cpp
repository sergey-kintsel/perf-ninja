#include "solution.hpp"

#include <algorithm>

static constexpr int TILE_SIZE = 4;
// before
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           2.98 ms         2.98 ms          178
// Performance counter stats for './lab':
//
//                18      context-switches                 #     17.2 cs/sec  cs_per_second
//                12      cpu-migrations                   #     11.5 migrations/sec  migrations_per_second
//            63,061      page-faults                      #  60358.6 faults/sec  page_faults_per_second
//          1,044.77 msec task-clock                       #      1.0 CPUs  CPUs_utilized
//           998,023      branch-misses                    #      0.4 %  branch_miss_rate         (49.97%)
//       246,706,945      branches                         #    236.1 M/sec  branch_frequency     (49.95%)
//     5,898,977,548      cpu-cycles                       #      5.6 GHz  cycles_frequency       (66.60%)
//     5,274,598,287      instructions                     #      0.9 instructions  insn_per_cycle  (50.06%)
//        67,019,404      stalled-cycles-frontend          #     0.01 frontend_cycles_idle        (50.08%)
//
//       1.045455031 seconds time elapsed
//
//       1.014349000 seconds user
//       0.031022000 seconds sys


// after
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           2.61 ms         2.61 ms          253
// Performance counter stats for './lab':
//
//                 21      context-switches                 #     20.5 cs/sec  cs_per_second
//                 11      cpu-migrations                   #     10.7 migrations/sec  migrations_per_second
//             63,060      page-faults                      #  61474.6 faults/sec  page_faults_per_second
//           1,025.79 msec task-clock                       #      1.0 CPUs  CPUs_utilized
//            753,111      branch-misses                    #      0.0 %  branch_miss_rate         (49.97%)
//      2,092,546,488      branches                         #   2039.9 M/sec  branch_frequency     (50.00%)
//      5,813,571,567      cpu-cycles                       #      5.7 GHz  cycles_frequency       (66.66%)
//     16,031,850,212      instructions                     #      2.8 instructions  insn_per_cycle  (50.06%)
//         79,596,934      stalled-cycles-frontend          #     0.01 frontend_cycles_idle        (50.03%)
//
//        1.032688971 seconds time elapsed
//
//        0.987414000 seconds user
//        0.038794000 seconds sys

bool solution(MatrixOfDoubles &in, MatrixOfDoubles &out) {
  using std::min;

  const int size = in.size();
  for (int ii{}; ii < size; ii += TILE_SIZE) {
    for (int jj{}; jj < size; jj += TILE_SIZE) {
      const auto max_i{min(size, ii + TILE_SIZE)};
      const auto max_j{min(size, jj + TILE_SIZE)};
      for (int i{ii}; i < max_i; i++) {
        for (int j{jj}; j < max_j; j++) {
          out[i][j] = in[j][i];
        }
      }
    }
  }
  return out[0][size - 1];
}
