#include "00_main.h"

// This was adapted from
// https://github.com/rbenchmark/benchmarks/blob/master/R-benchmark-25/
// The changes are:
// 1. Rewriting the tests in Armadillo allowing to change the matrix size
// 2. Moving the Armadillo tests to base R in a comparable way (i.e.,
//    using qr.solve() instead of lm())

// FFT over N random values

[[cpp11::register]] int matrix_functions_01_arma_(const int& n) {
  vec a = randn<vec>(n);
  cx_vec b = fft(a);
  return 0;
}

// Eigenvalues of an NxX random matrix

[[cpp11::register]] int matrix_functions_02_arma_(const int& n) {
  mat a = randn<mat>(n, n);
  cx_vec b = eig_gen(a);
  return 0;
}

// Determinant of an NxN random matrix

[[cpp11::register]] int matrix_functions_03_arma_(const int& n) {
  mat a = randn<mat>(n, n);
  double b = det(a);  // creates warning: unused variable ‘b’ but it's ok
  return 0;
}

// Cholesky decomposition of an NxN matrix

[[cpp11::register]] int matrix_functions_04_arma_(const int& n) {
  mat a = randn<mat>(n, n);
  a = a.t() * a;
  mat b = chol(a);
  return 0;
}

// Inverse of an NxN random matrix

[[cpp11::register]] int matrix_functions_05_arma_(const int& n) {
  mat a = randn<mat>(n, n);
  mat b = inv(a);
  return 0;
}
