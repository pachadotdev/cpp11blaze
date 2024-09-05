#include "00_main.h"

// This was adapted from
// https://github.com/rbenchmark/benchmarks/blob/master/R-benchmark-25/
// The changes are:
// 1. Rewriting the tests in Blaze allowing to change the matrix size
// 2. Moving the Blaze tests to base R in a comparable way (i.e.,
//    using qr.solve() instead of lm())

// N Fibonacci numbers calculation

[[cpp11::register]] int programmation_01_blaze_(const int& n) {
  double phi = 1.6180339887498949;

  DynamicVector<double, columnVector> a(n);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    a[i] = floor(rand<double>() * 1000);
  }

  DynamicVector<double, columnVector> b(n);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    b[i] = (pow(phi, a[i]) - pow(-phi, -a[i])) / sqrt(5);
  }

  return 0;
}

// Creation of an NxN Hilbert matrix

[[cpp11::register]] int programmation_02_blaze_(const int& n) {
  DynamicMatrix<double, columnMajor> a(n, n);

#ifdef _OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      a(i, j) = 1.0 / (i + j + 1);
    }
  }

  return 0;
}

// Grand common divisors of N pairs

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  } else {
    return gcd(b, a % b);
  }
}

[[cpp11::register]] int programmation_03_blaze_(const int& n) {
  DynamicVector<double, columnVector> a(n);
  DynamicVector<double, columnVector> b(n);
  DynamicVector<double, columnVector> c(n);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    a[i] = ceil(rand<double>() * 1000);
    b[i] = ceil(rand<double>() * 1000);
  }

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    c[i] = gcd(a[i], b[i]);  // gcd is a recursive function
  }

  return 0;
}

// Creation of an NxN Toeplitz matrix

[[cpp11::register]] int programmation_04_blaze_(const int& n) {
  DynamicMatrix<double, columnMajor> a(n, n);

#ifdef _OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      a(i, j) = abs(i - j) + 1;
    }
  }

  return 0;
}

// Escoufier's method on an NxN matrix

[[cpp11::register]] int programmation_05_blaze_(const int& n) {
  std::normal_distribution<double> d(0, 1);

  DynamicMatrix<double, columnMajor> x(n, n);

#ifdef _OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      x(i, j) = abs(d(random_normal()));
    }
  }

  DynamicVector<int, columnVector> vt(n);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    vt[i] = i + 1;
  }

  DynamicVector<int, columnVector> vr(n, 0);
  DynamicVector<double, columnVector> RV(n, 0.0);

  for (int j = 1; j <= n; ++j) {
    double Rvmax = 0.0;
    int vrt = 0;

    for (int k = 1; k <= (n - j + 1); ++k) {
      DynamicMatrix<double, columnMajor> x2 = x;
      if (j > 1) {
        for (int m = 0; m < j - 1; ++m) {
          auto col = column(x, vt[k - 1] - 1);
          DynamicMatrix<double, columnMajor> colMatrix(col.size(), 1);
          for (int i = 0; i < n; ++i) {
            colMatrix(i, 0) = col[i];
          }

          x2 = hstack(x2, colMatrix);
        }
      }

      auto col2 = column(x, vt[k - 1] - 1);
      DynamicMatrix<double, columnMajor> colMatrix2(col2.size(), 1);
      for (int i = 0; i < n; ++i) {
        colMatrix2(i, 0) = col2[i];
      }

      x2 = hstack(x2, colMatrix2);

      // Calculate correlation matrix
      DynamicMatrix<double, columnMajor> R = cor(x2);

      // Extract submatrices
      auto Ryy = submatrix(R, 0, 0, n, n);
      auto Rxx = submatrix(R, n, n, j, j);
      auto Rxy = submatrix(R, n, 0, j, n);
      auto Ryx = trans(Rxy);

      // Calculate traces
      double trace_Ryx_Rxy = trace(Ryx * Rxy);
      double trace_Ryy_Ryy = trace(Ryy * Ryy);
      double trace_Rxx_Rxx = trace(Rxx * Rxx);

      // Calculate RV coefficient
      double rvt = trace_Ryx_Rxy / std::sqrt(trace_Ryy_Ryy * trace_Rxx_Rxx);

      // Update Rvmax and vrt
      if (rvt > Rvmax) {
        Rvmax = rvt;
        vrt = vt[k - 1];
      }
    }

    // Update vr and RV
    vr[j - 1] = vrt;
    RV[j - 1] = Rvmax;

    // Remove vrt from vt
    size_t count = 0;
    for (size_t i = 0; i < vt.size(); ++i) {
      if (vt[i] != vrt) {
        ++count;
      }
    }
    DynamicVector<int, columnVector> filtered_vt(count);
    size_t index = 0;
    for (size_t i = 0; i < vt.size(); ++i) {
      if (vt[i] != vrt) {
        filtered_vt[index++] = vt[i];
      }
    }

    vt = filtered_vt;
  }

  return 0;
}
