#include "00_main.h"

[[cpp11::register]] doubles_matrix<> chol_mat(const doubles_matrix<>& x) {
  DynamicMatrix<double, columnMajor> X = as_DynamicMatrix(x);
  DynamicMatrix<double, columnMajor> L(X.rows(), X.columns());
  llh(X, L);
  return as_doubles_matrix(L);
}
