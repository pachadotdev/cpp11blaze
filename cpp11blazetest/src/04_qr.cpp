#include "00_main.h"

#include <iostream>

// The same example from the first script but using QR instead of directly
// obtaining the inverse

DynamicMatrix<double, columnMajor> ols_qr_(const doubles_matrix<>& y,
                                           const doubles_matrix<>& x) {
  DynamicMatrix<double, columnMajor> Y = as_DynamicMatrix(y);
  DynamicMatrix<double, columnMajor> X = as_DynamicMatrix(x);
  DynamicMatrix<double, columnMajor> Q;
  DynamicMatrix<double, columnMajor> R;
  qr(X, Q, R);
  return solve(R, trans(Q) * Y);
}

[[cpp11::register]] doubles_matrix<> ols_qr_mat(const doubles_matrix<>& y,
                                                const doubles_matrix<>& x) {
  DynamicMatrix<double, columnMajor> beta = ols_qr_(y, x);
  return as_doubles_matrix(beta);
}

[[cpp11::register]] doubles ols_qr_dbl(const doubles_matrix<>& y,
                                       const doubles_matrix<>& x) {
  DynamicMatrix<double, columnMajor> beta = ols_qr_(y, x);
  return as_doubles(beta);
}
