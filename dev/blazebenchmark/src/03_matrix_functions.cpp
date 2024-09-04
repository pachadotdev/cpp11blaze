#include "00_main.h"

// This was adapted from
// https://github.com/rbenchmark/benchmarks/blob/master/R-benchmark-25/
// The changes are:
// 1. Rewriting the tests in Blaze allowing to change the matrix size
// 2. Moving the Blaze tests to base R in a comparable way (i.e.,
//    using qr.solve() instead of lm())

// FFT over N random values

[[cpp11::register]] int matrix_functions_01_arma_(const int& n) {
  std::normal_distribution<double> d(0, 1);

  DynamicVector<double, columnVector> a(n);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for(int i = 0; i < n; ++i) {
    a[i] = d(random_normal());
  }

  fftw_complex* in = reinterpret_cast<fftw_complex*>(a.data());
  fftw_complex* out =
      reinterpret_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * n));
  fftw_plan plan = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(plan);

  DynamicVector<complex<double>, columnVector> b(n);
  for (int i = 0; i < n; ++i) {
    b[i] = complex<double>(out[i][0], out[i][1]);
  }

  fftw_destroy_plan(plan);
  fftw_free(out);

  return 0;
}

// Eigenvalues of an NxX random matrix

[[cpp11::register]] int matrix_functions_02_arma_(const int& n) {
  std::normal_distribution<double> d(0, 1);

  DynamicMatrix<double, columnMajor> a(n, n);

#ifdef _OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      a(i, j) = d(random_normal());
    }
  }

  DynamicVector<std::complex<double>, columnVector> eigenvalues;
  geev(a, eigenvalues);

  return 0;
}

// Determinant of an NxN random matrix

[[cpp11::register]] int matrix_functions_03_arma_(const int& n) {
  std::normal_distribution<double> d(0, 1);

  DynamicMatrix<double, columnMajor> a(n, n);

#ifdef _OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      a(i, j) = d(random_normal());
    }
  }

  double b = det(a);  // creates warning: unused variable ‘b’ but it's ok
  return 0;
}

// Cholesky decomposition of an NxN matrix

[[cpp11::register]] int matrix_functions_04_arma_(const int& n) {
  std::normal_distribution<double> d(0, 1);

  DynamicMatrix<double, columnMajor> a(n, n);

#ifdef _OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      a(i, j) = d(random_normal());
    }
  }

  a = a.transpose() * a;

  DynamicMatrix<double, columnMajor> l(a.rows(), a.columns());
  llh(a, l);

  return 0;
}

// Inverse of an NxN random matrix

[[cpp11::register]] int matrix_functions_05_arma_(const int& n) {
  std::normal_distribution<double> d(0, 1);

  DynamicMatrix<double, columnMajor> a(n, n);

#ifdef _OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      a(i, j) = d(random_normal());
    }
  }

  DynamicMatrix<double, columnMajor> b = inv(a);
  
  return 0;
}
