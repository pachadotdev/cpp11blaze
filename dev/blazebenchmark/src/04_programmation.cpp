#include "00_main.h"

// This was adapted from
// https://github.com/rbenchmark/benchmarks/blob/master/R-benchmark-25/
// The changes are:
// 1. Rewriting the tests in Blaze allowing to change the matrix size
// 2. Moving the Blaze tests to base R in a comparable way (i.e.,
//    using qr.solve() instead of lm())

// N Fibonacci numbers calculation

[[cpp11::register]] int programmation_01_arma_(const int& n) {
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

[[cpp11::register]] int programmation_02_arma_(const int& n) {
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

[[cpp11::register]] int programmation_03_arma_(const int& n) {
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

[[cpp11::register]] int programmation_04_arma_(const int& n) {
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

[[cpp11::register]] int programmation_05_arma_(const int& n) {
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

  DynamicVector<double, columnVector> vt = linspace<double>(
      1.0, static_cast<double>(n), static_cast<int>(n)); // Variables to test
  DynamicVector<double, columnVector> vr(n);             // Result: ordered variables
  DynamicVector<double, columnVector> RV(n);             // Result: correlations
  DynamicMatrix<double, columnMajor> x2, R, Ryy, Rxx, Rxy, Ryx;
  double vrt, Rvmax, trace_Ryx_Rxy, trace_Ryy_Ryy, trace_Rxx_Rxx, rvt;

  for (int j = 0; j < n; ++j) {  // loop on the variable number
    Rvmax = 0;
    for (int k = 0; k < (n - j); ++k) {  // loop on the variables
      if (j == 0) {
        auto col = column(x, static_cast<int>(vt[k]) - 1);
        DynamicMatrix<double> colMatrix(col.size(), 1);
        for (int i = 0; i < col.size(); ++i) {
          colMatrix(i, 0) = col[i];
        }
        x2 = hstack(x, colMatrix);
      } else {
        DynamicVector<int, columnVector> vr_indices(j);
        for (size_t i = 0; i < j; ++i) {
          vr_indices[i] = static_cast<int>(vr[i]) - 1;
        }
        DynamicMatrix<double, columnMajor> selected_cols(x.rows(),
          vr_indices.size());
        for (size_t i = 0; i < vr_indices.size(); ++i) {
          column(selected_cols, i) = column(x, vr_indices[i]);
        }
        auto col = column(x, static_cast<int>(vt[k]) - 1);
        DynamicMatrix<double> colMatrix(col.size(), 1);
        for (int i = 0; i < col.size(); ++i) {
          colMatrix(i, 0) = col[i];
        }
        x2 = hstack(x, hstack(selected_cols, colMatrix));
      }
      R = cor(x2);  // Correlations table
      Ryy = submatrix(R, 0, 0, n - 1, n - 1);
      Rxx = submatrix(R, n, n, n + j, n + j);
      Rxy = submatrix(R, n, 0, n + j, n - 1);
      Ryx = trans(Rxy);
      trace_Ryx_Rxy = trace(Ryx * Rxy);
      trace_Ryy_Ryy = trace(Ryy * Ryy);
      trace_Rxx_Rxx = trace(Rxx * Rxx);
      rvt = trace_Ryx_Rxy / sqrt(trace_Ryy_Ryy * trace_Rxx_Rxx);  // RV calculation
      if (rvt > Rvmax) {
        Rvmax = rvt;  // test of RV
        vrt = vt[k];  // temporary held variable
      }
    }
    vr[j] = vrt;    // Result: variable
    RV[j] = Rvmax;  // Result: correlation

    for (size_t i = 0; i < vt.size(); ++i) {
      if (vt[i] == vr[j]) {
        DynamicVector<double, columnVector> new_vt(vt.size() - 1);
        for (size_t j = 0, k = 0; j < vt.size(); ++j) {
          if (j != i) {
            new_vt[k++] = vt[j];
          }
        }
        vt = new_vt;
        break;
      }
    }
  }
  return 0;
}
