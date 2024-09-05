#include "00_main.h"

// Random normal values

std::mt19937& random_normal() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  return gen;
}

// Correlation

DynamicMatrix<double> cor(const DynamicMatrix<double>& x) {
  size_t n = x.rows();
  DynamicMatrix<double> R(n, n);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      double mean_i = mean(column(x, i));
      double mean_j = mean(column(x, j));
      double cov_ij = dot(column(x, i) - mean_i, column(x, j) - mean_j) / (n - 1);
      double std_i = std::sqrt(dot(column(x, i) - mean_i, column(x, i) - mean_i) / (n - 1));
      double std_j = std::sqrt(dot(column(x, j) - mean_j, column(x, j) - mean_j) / (n - 1));
      R(i, j) = cov_ij / (std_i * std_j);
    }
  }
  return R;
}

DynamicMatrix<double, columnMajor> hstack(const DynamicMatrix<double, columnMajor>& A,
  const DynamicMatrix<double, columnMajor>& B) {
  DynamicMatrix<double, columnMajor> result(A.rows(), A.columns() + B.columns());
  submatrix(result, 0, 0, A.rows(), A.columns()) = A;
  submatrix(result, 0, A.columns(), B.rows(), B.columns()) = B;
  return result;
}
