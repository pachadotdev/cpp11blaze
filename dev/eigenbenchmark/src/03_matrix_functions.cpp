#include "00_main.h"

// This was adapted from
// https://github.com/rbenchmark/benchmarks/blob/master/R-benchmark-25/
// The changes are:
// 1. Rewriting the tests in Armadillo allowing to change the matrix size
// 2. Moving the Armadillo tests to base R in a comparable way (i.e.,
//    using qr.solve() instead of lm())

// FFT over N random values

[[cpp11::register]] int matrix_functions_01_eigen_(const int& n) {
  std::normal_distribution<double> d(0, 1);
  VectorXd a = VectorXd::NullaryExpr(n, [&]() { return d(random_normal()); });

  Eigen::FFT<double> fft;
  Eigen::VectorXcd b(n);
  fft.fwd(b, a);

  return 0;
}

// Eigenvalues of an NxX random matrix

[[cpp11::register]] int matrix_functions_02_eigen_(const int& n) {
  std::normal_distribution<double> d(0, 1);
  MatrixXd a = MatrixXd::NullaryExpr(n, n, [&]() { return d(random_normal()); });
  EigenSolver<MatrixXd> solver(a);
  VectorXcd b = solver.eigenvalues();
  return 0;
}

// Determinant of an NxN random matrix

[[cpp11::register]] int matrix_functions_03_eigen_(const int& n) {
  std::normal_distribution<double> d(0, 1);
  MatrixXd a = MatrixXd::NullaryExpr(n, n, [&]() { return d(random_normal()); });
  double b = a.determinant();  // creates warning: unused variable ‘b’ but it's ok
  return 0;
}

// Cholesky decomposition of an NxN matrix

[[cpp11::register]] int matrix_functions_04_eigen_(const int& n) {
  std::normal_distribution<double> d(0, 1);
  MatrixXd a = MatrixXd::NullaryExpr(n, n, [&]() { return d(random_normal()); });
  a = a.transpose() * a;
  LLT<MatrixXd> lltOfA(a);
  MatrixXd b = lltOfA.matrixL();
  return 0;
}

// Inverse of an NxN random matrix

[[cpp11::register]] int matrix_functions_05_eigen_(const int& n) {
  std::normal_distribution<double> d(0, 1);
  MatrixXd a = MatrixXd::NullaryExpr(n, n, [&]() { return d(random_normal()); });
  MatrixXd b = a.inverse();
  return 0;
}
