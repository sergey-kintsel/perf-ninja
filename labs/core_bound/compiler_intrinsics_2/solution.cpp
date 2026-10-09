#include "solution.hpp"
#include <benchmark/benchmark_api.h>
#include <benchmark/utils.h>
#include <immintrin.h>
#include <iostream>

// baseline
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1            247 us          247 us         2831

// with avx512
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
// -----------------------------------------------------
// bench1           38.9 us         38.9 us        17625

// Find the longest line in a file.
// Implementation uses ternary operator with a hope that compiler will
// turn it into a CMOV instruction.
// The code inside the inner loop is equivalent to:
/*
if (s == '\n') {
  longestLine = std::max(curLineLength, longestLine);
  curLineLength = 0;
} else {
  curLineLength++;
}*/
unsigned solution(const std::string &inputContents) {
  size_t longestLine = 0;
  size_t start = 0;
  const size_t len = inputContents.size();

  __m512i newline_chars = _mm512_set1_epi8('\n');

  size_t i{};
  for (; i + 64 < len;) {
    __m512i chars = _mm512_loadu_epi8(inputContents.data() + i);
    __mmask64 mask = _mm512_cmp_epi8_mask(chars, newline_chars, _MM_CMPINT_EQ);

    if (mask) {
      size_t end = std::countr_zero(mask);
      longestLine = std::max(longestLine, i + end - start);
      start = i + end + 1;
      i += end + 1;
    } else {
      i += 64;
    }
  }

  for (; i < len; ++i) {
    if (inputContents[i] == '\n') {
      longestLine = std::max(longestLine, i - start);
      start = i + 1;
    }
  }

  longestLine = std::max(longestLine, i - start);

  return longestLine;
}
