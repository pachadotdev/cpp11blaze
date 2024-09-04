#include "00_main.h"

// adapted from 10.21105/joss.01866

[[cpp11::register]] doubles_matrix<> balassa_eigen_(const doubles_matrix<>& x) {
  MatrixXd X = as_Matrix(x);

  MatrixXd B = X.array().colwise() / X.rowwise().sum().array();
  B = B.array().rowwise() / (X.colwise().sum().array() / X.sum());
  B = (B.array() < 1).select(0, B);
  B = (B.array() >= 1).select(1, B);

  return as_doubles_matrix(B);
}
