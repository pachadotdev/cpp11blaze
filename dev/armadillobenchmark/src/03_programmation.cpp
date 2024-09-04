#include "00_main.h"

// This was adapted from
// https://github.com/rbenchmark/benchmarks/blob/master/R-benchmark-25/
// The changes are:
// 1. Rewriting the tests in Armadillo allowing to change the matrix size
// 2. Moving the Armadillo tests to base R in a comparable way (i.e.,
//    using qr.solve() instead of lm())

// N Fibonacci numbers calculation

[[cpp11::register]] int programmation_01_arma_(const int& n) {
  double phi = 1.6180339887498949;
  vec a = floor(randu<vec>(n) * 1000);
  vec b(n);
  for (int i = 0; i < n; ++i) {
    b(i) = (pow(phi, a(i)) - pow(-phi, -a(i))) / sqrt(5);
  }
  return 0;
}

// Creation of an NxN Hilbert matrix

[[cpp11::register]] int programmation_02_arma_(const int& n) {
  mat a(n, n);
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
  vec a = ceil(randu<vec>(n) * 1000);
  vec b = ceil(randu<vec>(n) * 1000);
  vec c(n);
  for (int i = 0; i < n; ++i) {
    c(i) = gcd(a(i), b(i));  // gcd is a recursive function
  }
  return 0;
}

// Creation of an NxN Toeplitz matrix

[[cpp11::register]] int programmation_04_arma_(const int& n) {
  mat a(n, n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      a(i, j) = abs(i - j) + 1;
    }
  }
  return 0;
}

// Escoufier's method on an NxN matrix

[[cpp11::register]] int programmation_05_arma_(const int& n) {
  mat x = abs(randn<mat>(n, n));
  vec vt = linspace<vec>(1, n, n);  // Variables to test
  vec vr(n);                        // Result: ordered variables
  vec RV(n);                        // Result: correlations
  mat x2, R, Ryy, Rxx, Rxy, Ryx;
  double vrt, Rvmax, trace_Ryx_Rxy, trace_Ryy_Ryy, trace_Rxx_Rxx, rvt;

  for (int j = 0; j < n; ++j) {  // loop on the variable number
    Rvmax = 0;
    for (int k = 0; k < (n - j); ++k) {  // loop on the variables
      if (j == 0) {
        x2 = join_horiz(x, x.col(vt(k) - 1));
      } else {
        uvec vr_indices = conv_to<uvec>::from(vr.head(j)) - 1;
        x2 = join_horiz(x, x.cols(vr_indices), x.col(vt(k) - 1));
      }
      R = cor(x2);  // Correlations table
      Ryy = R.submat(0, 0, n - 1, n - 1);
      Rxx = R.submat(n, n, n + j, n + j);
      Rxy = R.submat(n, 0, n + j, n - 1);
      Ryx = Rxy.t();
      trace_Ryx_Rxy = trace(Ryx * Rxy);
      trace_Ryy_Ryy = trace(Ryy * Ryy);
      trace_Rxx_Rxx = trace(Rxx * Rxx);
      rvt = trace_Ryx_Rxy / sqrt(trace_Ryy_Ryy * trace_Rxx_Rxx);  // RV calculation
      if (rvt > Rvmax) {
        Rvmax = rvt;  // test of RV
        vrt = vt(k);  // temporary held variable
      }
    }
    vr(j) = vrt;    // Result: variable
    RV(j) = Rvmax;  // Result: correlation
    uvec idx = find(vt == vr(j));
    if (!idx.is_empty()) {
      vt.shed_row(idx(0));  // reidentify variables to test
    }
  }
  return 0;
}
