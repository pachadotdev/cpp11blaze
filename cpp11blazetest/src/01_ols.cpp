#include "00_main.h"

DynamicMatrix<double> ols_(const doubles_matrix<>& y, const doubles_matrix<>& x) {
  DynamicMatrix<double, columnMajor> Y = as_DynamicMatrix(y);
  // DynamicVector<double, columnVector> Y = as_DynamicVector(y); also works

  DynamicMatrix<double, columnMajor> X = as_DynamicMatrix(x);

  DynamicMatrix<double, columnMajor> XtX = trans(X) * X;             // X'X
  DynamicMatrix<double, columnMajor> XtX_inv = inv(XtX);             // (X'X)^(-1)
  DynamicMatrix<double, columnMajor> beta = XtX_inv * trans(X) * Y;  // (X'X)^(-1)(X'Y)

  return beta;
}

[[cpp11::register]] doubles_matrix<> ols_mat(const doubles_matrix<>& y,
                                             const doubles_matrix<>& x) {
  DynamicMatrix<double, columnMajor> beta = ols_(y, x);
  return as_doubles_matrix(beta);
}

[[cpp11::register]] doubles ols_vec(const doubles_matrix<>& y,
                                    const doubles_matrix<>& x) {
  DynamicMatrix<double, columnMajor> beta = ols_(y, x);

  return as_doubles(beta);
}
