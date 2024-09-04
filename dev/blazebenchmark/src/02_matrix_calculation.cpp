#include "00_main.h"

// This was adapted from
// https://github.com/rbenchmark/benchmarks/blob/master/R-benchmark-25/
// The changes are:
// 1. Rewriting the tests in Blaze allowing to change the matrix size
// 2. Moving the Blaze tests to base R in a comparable way (i.e.,
//    using qr.solve() instead of lm())

// Creation, transposition, deformation of an NxN matrix

[[cpp11::register]] int matrix_calculation_01_arma_(const int& n) {
  std::normal_distribution<double> d(0, 1);

  DynamicMatrix<double, columnMajor> a(n, n);

#ifdef _OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      a(i, j) = d(random_normal()) / 10;
    }
  }

  DynamicMatrix<double, columnMajor> b = trans(a);
  b.resize(n / 2, n * 2, true);
  return 0;
}

// NxN normal distributed random matrix^1000

[[cpp11::register]] int matrix_calculation_02_arma_(const int& n) {
  std::normal_distribution<double> d(0, 1);

  DynamicMatrix<double, columnMajor> a(n, n);

#ifdef _OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      a(i, j) = std::abs(d(random_normal())) / 2;
    }
  }

  DynamicMatrix<double, columnMajor> b = pow(a, 1000);
  return 0;
}

// Sorting of N random values

[[cpp11::register]] int matrix_calculation_03_arma_(const int& n) {
  std::normal_distribution<double> d(0, 1);

  DynamicVector<double, columnVector> a(n);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    a[i] = d(random_normal());
  }

  std::sort(a.begin(), a.end());

  return 0;
}

// NxN cross-product matrix

[[cpp11::register]] int matrix_calculation_04_arma_(const int& n) {
  std::normal_distribution<double> d(0, 1);

  DynamicMatrix<double, columnMajor> a(n, n);

#ifdef _OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      a(i, j) = d(random_normal());
    }
  }

  DynamicMatrix<double, columnMajor> b = a.transpose() * a;
  
  return 0;
}

// Linear regression over an NxN matrix

[[cpp11::register]] int matrix_calculation_05_arma_(const int& n) {
  std::normal_distribution<double> d(0, 1);

  DynamicMatrix<double, columnMajor> x(n, n);
  DynamicVector<double, columnVector> y(n);

#ifdef _OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      x(i, j) = d(random_normal());
    }
  }

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    y[i] = d(random_normal());
  }

  DynamicVector<double, columnVector> c = solve(x.transpose(), x.transpose() * y);
  
  return 0;
}
