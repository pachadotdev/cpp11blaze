#include "00_main.h"

// Random normal values

std::mt19937& random_normal() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  return gen;
}

// MATLAB-like linspace

template <typename T>
DynamicVector<T, columnVector> linspace(T start, T end, std::size_t num) {
  DynamicVector<T, columnVector> result(num);
  if (num == 0) {
    return result;
  }
  if (num == 1) {
    result[0] = start;
    return result;
  }
  T step = (end - start) / (num - 1);
  for (std::size_t i = 0; i < num; ++i) {
    result[i] = start + i * step;
  }
  return result;
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

DynamicMatrix<double> hstack(const DynamicMatrix<double>& A,
                             const DynamicMatrix<double>& B) {
  DynamicMatrix<double> result(A.rows(), A.columns() + B.columns());
  submatrix(result, 0, 0, A.rows(), A.columns()) = A;
  submatrix(result, 0, A.columns(), B.rows(), B.columns()) = B;
  return result;
}
