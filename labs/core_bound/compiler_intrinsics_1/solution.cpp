
#include "solution.h"
#include <immintrin.h>
#include <memory>

// baseline
// ------------------------------------------------------------
// Benchmark                  Time             CPU   Iterations
// ------------------------------------------------------------
// bench_partial_sum       14.4 us         14.4 us        47772

// with simplified accumulation
// ------------------------------------------------------------
// Benchmark                  Time             CPU   Iterations
// ------------------------------------------------------------
// bench_partial_sum       8.71 us         8.71 us        78344

// with manual intrinsics
// ------------------------------------------------------------
// Benchmark                  Time             CPU   Iterations
// ------------------------------------------------------------
// bench_partial_sum       3.67 us         3.67 us       180391

void imageSmoothing(const InputVector &input, uint8_t radius,
                    OutputVector &output) {
  int pos = 0;
  int currentSum = 0;
  int size = static_cast<int>(input.size());

  // 1. left border - time spend in this loop can be ignored, no need to
  // optimize it
  for (int i = 0; i < std::min<int>(size, radius); ++i) {
    currentSum += input[i];
  }

  int limit = std::min(radius + 1, size - radius);
  for (pos = 0; pos < limit; ++pos) {
    currentSum += input[pos + radius];
    output[pos] = currentSum;
  }

  // 2. main loop.
  limit = size - radius;

  for (__m128i current = _mm_set1_epi16(currentSum); pos + 7 < limit;
       pos += 8) {
    __m128i left = _mm_loadu_si64(input.data() + pos - radius - 1);
    __m128i right = _mm_loadu_si64(input.data() + pos + radius);
    __m128i left16b = _mm_cvtepu8_epi16(left);
    __m128i right16b = _mm_cvtepu8_epi16(right);

    __m128i subtracted = _mm_sub_epi16(right16b, left16b);

    __m128i delta = _mm_add_epi16(subtracted, _mm_slli_si128(subtracted, 2));

    delta = _mm_add_epi16(delta, _mm_slli_si128(subtracted, 2));
    delta = _mm_add_epi16(delta, _mm_slli_si128(subtracted, 4));
    delta = _mm_add_epi16(delta, _mm_slli_si128(subtracted, 8));

    __m128i result = _mm_add_epi16(delta, current);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(output.data() + pos), result);
    currentSum = static_cast<uint16_t>(_mm_extract_epi16(result, 7));
  }

  // 3. special case, executed only if size <= 2*radius + 1
  limit = std::min(radius + 1, size);
  for (; pos < limit; pos++) {
    output[pos] = currentSum;
  }

  // 4. right border - time spend in this loop can be ignored, no need to
  // optimize it
  for (; pos < size; ++pos) {
    currentSum -= input[pos - radius - 1];
    output[pos] = currentSum;
  }
}
