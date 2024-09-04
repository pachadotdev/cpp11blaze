#include "00_main.h"

// This was adapted from
// https://github.com/rbenchmark/benchmarks/blob/master/R-benchmark-25/
// The changes are:
// 1. Rewriting the tests in Armadillo allowing to change the matrix size
// 2. Moving the Armadillo tests to base R in a comparable way (i.e.,
//    using qr.solve() instead of lm())

// N Fibonacci numbers calculation

[[cpp11::register]] int programmation_01_eigen_(const int& n) {
  double phi = 1.6180339887498949;
  VectorXd a =
      (VectorXd::Random(n) * 1000).unaryExpr([](double x) { return std::floor(x); });
  VectorXd b(n);
  for (int i = 0; i < n; ++i) {
    b(i) = (pow(phi, a(i)) - pow(-phi, -a(i))) / sqrt(5);
  }
  return 0;
}

// Creation of an NxN Hilbert matrix

[[cpp11::register]] int programmation_02_eigen_(const int& n) {
  MatrixXd a(n, n);
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

[[cpp11::register]] int programmation_03_eigen_(const int& n) {
  VectorXd a =
      (VectorXd::Random(n) * 1000).unaryExpr([](double x) { return std::ceil(x); });
  VectorXd b =
      (VectorXd::Random(n) * 1000).unaryExpr([](double x) { return std::ceil(x); });
  VectorXd c(n);
  for (int i = 0; i < n; ++i) {
    c(i) = gcd(a(i), b(i));  // gcd is a recursive function
  }
  return 0;
}

// Creation of an NxN Toeplitz matrix

[[cpp11::register]] int programmation_04_eigen_(const int& n) {
  MatrixXd a(n, n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      a(i, j) = abs(i - j) + 1;
    }
  }
  return 0;
}

// Escoufier's method on an NxN matrix

MatrixXd cor(const MatrixXd& x) {
  int n = x.rows();
  VectorXd mean = x.colwise().mean();
  MatrixXd centered = x.rowwise() - mean.transpose();
  MatrixXd cov = (centered.transpose() * centered) / (n - 1);
  VectorXd stddev = cov.diagonal().array().sqrt();
  MatrixXd corr = cov.array().colwise() / stddev.array();
  corr = corr.array().rowwise() / stddev.transpose().array();
  return corr;
}

[[cpp11::register]] int programmation_05_eigen_(const int& n) {
  std::normal_distribution<double> d(0, 1);
  MatrixXd x =
      MatrixXd::NullaryExpr(n, n, [&]() { return std::abs(d(random_normal())); });

  // Variables to test
  VectorXd vt = Eigen::VectorXd::LinSpaced(n, 1, n);
  VectorXd vr(n);  // Result: ordered variables
  VectorXd RV(n);  // Result: correlations
  MatrixXd x2, R, Ryy, Rxx, Rxy, Ryx;
  double vrt, Rvmax, trace_Ryx_Rxy, trace_Ryy_Ryy, trace_Rxx_Rxx, rvt;

  for (int j = 0; j < n; ++j) {  // loop on the variable number
    Rvmax = 0;
    for (int k = 0; k < (n - j); ++k) {  // loop on the variables
      if (j == 0) {
        x2.resize(x.rows(), x.cols() + 1);
        x2 << x, x.col(static_cast<int>(vt(k)) - 1);
      } else {
        VectorXi vr_indices = (vr.head(j).array() - 1).cast<int>();
        x2.resize(x.rows(), x.cols() + vr_indices.size() + 1);
        x2 << x, x(Eigen::all, vr_indices), x.col(static_cast<int>(vt(k)) - 1);
      }
      R = cor(x2);  // Correlations table
      Ryy = R.topLeftCorner(n, n);
      Rxx = R.bottomRightCorner(j + 1, j + 1);
      Rxy = R.bottomLeftCorner(j + 1, n);
      Ryx = Rxy.transpose();
      trace_Ryx_Rxy = (Ryx * Rxy).trace();
      trace_Ryy_Ryy = (Ryy * Ryy).trace();
      trace_Rxx_Rxx = (Rxx * Rxx).trace();
      rvt = trace_Ryx_Rxy / std::sqrt(trace_Ryy_Ryy * trace_Rxx_Rxx);  // RV calculation
      if (rvt > Rvmax) {
        Rvmax = rvt;  // test of RV
        vrt = vt(k);  // temporary held variable
      }
    }
    vr(j) = vrt;    // Result: variable
    RV(j) = Rvmax;  // Result: correlation
    VectorXi idx = (vt.array() == vr(j)).cast<int>();
    if (idx.sum() > 0) {
      vt = vt(seqN(0, idx.size() - 1)).eval();  // reidentify variables to test
    }
  }
  return 0;
}
