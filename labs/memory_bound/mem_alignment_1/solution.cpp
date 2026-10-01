
#include "solution.h"
#include <random>
#include <iostream>

// baseline
// -------------------------------------------------------
// Benchmark             Time             CPU   Iterations
// -------------------------------------------------------
// bench1/_63         17.8 us         17.8 us        37464
// bench1/_64         10.2 us         10.2 us        67955
// bench1/_65         12.9 us         12.9 us        53398
// bench1/_128        81.7 us         81.7 us         8499
// bench1/_256         711 us          711 us          989
// bench1/_511        7187 us         7186 us           98
// bench1/_512        5876 us         5876 us          119
// bench1/_513        7191 us         7191 us           96
// bench1/_1024      51173 us        51171 us           11

// with alignment
// -------------------------------------------------------
// Benchmark             Time             CPU   Iterations
// -------------------------------------------------------
// bench1/_63         14.5 us         14.5 us        45552
// bench1/_64         9.71 us         9.71 us        72402
// bench1/_65         10.3 us         10.3 us        68023
// bench1/_128        77.7 us         77.7 us         9011
// bench1/_256         627 us          627 us         1120
// bench1/_511        5457 us         5457 us          129
// bench1/_512        5072 us         5072 us          138
// bench1/_513        5338 us         5337 us          131
// bench1/_1024      42882 us        42880 us           16
//
// ******************************************
// Change this function
// ******************************************
// This function allows you to change the number of columns in a matrix. 
// In other words, it defines how many elements are in each row.
// hint: you need to allocate dummy columns to achieve proper data alignment.
int n_columns(int N) {
  return N % 16 ? (N + 16 - (N % 16)) : N;
}
// ******************************************

// DO NOT change any of the functions below.
// The following applies to all functions below:
// You will notice the functions have `K` argument in addition to `N`.
// This is because these functions are prepared for matrices with aligned rows.
// I.e. a matrix has N x N elements, but its actual dimensions are N x K since
// it has padding. However, only N x N elements are used.
void initRandom(Matrix &matrix, int N, int K) {
  std::default_random_engine generator;
  std::uniform_real_distribution<float> distribution(-0.95f, 0.95f);
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      matrix[i * K + j] = distribution(generator);
}

void initZero(Matrix &matrix, int N, int K) {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      matrix[i * K + j] = 0.0f;
}

void copyFromMatrix(const Matrix &from, Matrix &to, int N, int K) {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      to[i * K + j] = from[i * N + j];
}

// A simple GEMM. Use only for small matrices (up to 100 x 100)
void interchanged_matmul(float* RESTRICT A, 
                         float* RESTRICT B,
                         float* RESTRICT C, int N, int K) {
  for (int i = 0; i < N; ++i)
    for (int k = 0; k < N; ++k)
      for (int j = 0; j < N; ++j)
        C[i * K + j] += A[i * K + k] * B[k * K + j];
}

// Here is a blocked version for larger matrix sizes (e.g. 512 x 512 and beyond).
void blocked_matmul(float* RESTRICT A, 
                    float* RESTRICT B,
                    float* RESTRICT C, int N, int K) {
  constexpr int blockSize = 64;
  for (int ii = 0; ii < N; ii += blockSize)
    for (int kk = 0; kk < N; kk += blockSize)
      for (int jj = 0; jj < N; jj += blockSize)
        for (int i = ii; i < std::min(ii + blockSize, N); ++i)
          for (int k = kk; k < std::min(kk + blockSize, N); ++k)
            for (int j = jj; j < std::min(jj + blockSize, N); ++j)                        
              C[i * K + j] += A[i * K + k] * B[k * K + j];
}
