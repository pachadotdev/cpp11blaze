#include "00_main.h"

// This was adapted from
// https://github.com/rbenchmark/benchmarks/blob/master/R-benchmark-25/
// The changes are:
// 1. Rewriting the tests in Armadillo allowing to change the matrix size
// 2. Moving the Armadillo tests to base R in a comparable way (i.e.,
//    using qr.solve() instead of lm())

// Creation, transposition, deformation of an NxN matrix

[[cpp11::register]] int matrix_calculation_01_arma_(const int& n) {
  mat a = randn<mat>(n, n) / 10;
  mat b = a.t();
  b.reshape(n / 2, n * 2);
  return 0;
}

// NxN normal distributed random matrix^1000

[[cpp11::register]] int matrix_calculation_02_arma_(const int& n) {
  mat a = abs(randn<mat>(n, n) / 2);
  mat b = pow(a, 1000);
  return 0;
}

// Sorting of N random values

[[cpp11::register]] int matrix_calculation_03_arma_(const int& n) {
  vec a = randn<vec>(n);
  a = sort(a);
  return 0;
}

// NxN cross-product matrix

[[cpp11::register]] int matrix_calculation_04_arma_(const int& n) {
  mat a = randn<mat>(n, n);
  mat b = a.t() * a;
  return 0;
}

// Linear regression over an NxN matrix

[[cpp11::register]] int matrix_calculation_05_arma_(const int& n) {
  mat x = randn<mat>(n, n);
  vec y = randn<mat>(n);
  vec c = solve(x.t(), x.t() * y);
  return 0;
}
