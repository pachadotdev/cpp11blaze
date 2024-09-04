#include "00_main.h"

// vec = colvec = DynamicMatrix<double, columnMajor>

[[cpp11::register]] doubles typedef_Col_double(const doubles& x) {
  DynamicMatrix<double, columnMajor> y = as_DynamicMatrix(x);
  return as_doubles(y);
}

[[cpp11::register]] integers typedef_Col_int(const integers& x) {
  DynamicMatrix<int, columnMajor> y = as_DynamicMatrix(x);
  return as_integers(y);
}

[[cpp11::register]] doubles_matrix<> typedef_Mat_double(const doubles_matrix<>& x) {
  DynamicMatrix<double, columnMajor> y = as_DynamicMatrix(x);
  return as_doubles_matrix(y);
}

[[cpp11::register]] integers_matrix<> typedef_Mat_int(const integers_matrix<>& x) {
  DynamicMatrix<int, columnMajor> y = as_DynamicMatrix(x);
  return as_integers_matrix(y);
}
