#include "00_main.h"

// This was adapted from
// https://github.com/rbenchmark/benchmarks/blob/master/R-benchmark-25/
// The changes are:
// 1. Rewriting the tests in Armadillo allowing to change the matrix size
// 2. Moving the Armadillo tests to base R in a comparable way (i.e.,
//    using qr.solve() instead of lm())

// Creation, transposition, deformation of an NxN matrix

[[cpp11::register]] int matrix_calculation_01_eigen_(const int& n) {
  std::normal_distribution<double> d(0, 1);
  MatrixXd a = MatrixXd::NullaryExpr(n, n, [&]() { return d(random_normal()); }) / 10;
  MatrixXd b = a.transpose();
  b.resize(n / 2, n * 2);
  return 0;
}

// NxN normal distributed random matrix^1000

[[cpp11::register]] int matrix_calculation_02_eigen_(const int& n) {
  std::normal_distribution<double> d(0, 1);
  MatrixXd a =
      MatrixXd::NullaryExpr(n, n, [&]() { return std::abs(d(random_normal())); }) / 2;
  MatrixXd b = a.array().pow(1000);
  return 0;
}

// Sorting of N random values

[[cpp11::register]] int matrix_calculation_03_eigen_(const int& n) {
  std::normal_distribution<double> d(0, 1);
  VectorXd a = VectorXd::NullaryExpr(n, [&]() { return d(random_normal()); });
  std::sort(a.data(), a.data() + a.size());
  return 0;
}

// NxN cross-product matrix

[[cpp11::register]] int matrix_calculation_04_eigen_(const int& n) {
  std::normal_distribution<double> d(0, 1);
  MatrixXd a = MatrixXd::NullaryExpr(n, n, [&]() { return d(random_normal()); });
  MatrixXd b = a.transpose() * a;
  return 0;
}

// Linear regression over an NxN matrix

[[cpp11::register]] int matrix_calculation_05_eigen_(const int& n) {
  std::normal_distribution<double> d(0, 1);
  MatrixXd x = MatrixXd::NullaryExpr(n, n, [&]() { return d(random_normal()); });
  VectorXd y = VectorXd::NullaryExpr(n, [&]() { return d(random_normal()); });
  VectorXd c = x.transpose().colPivHouseholderQr().solve(x.transpose() * y);
  return 0;
}
