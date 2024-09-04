#include "00_main.h"

[[cpp11::register]] doubles_matrix<> capm(const doubles_matrix<>& r,
                                          const doubles_matrix<>& m, double f) {
  DynamicMatrix<double, columnMajor> R = as_DynamicMatrix(r);
  DynamicMatrix<double, columnMajor> M = as_DynamicMatrix(m);

  // Market average return
  double R_mean = mean(R);
  double M_mean = mean(M);
  R -= R_mean;
  M -= M_mean;

  // CAPM betas
  DynamicMatrix<double, columnMajor> cov = trans(R) * M / (R.rows() - 1);
  double var = sum(trans(M) * M) / (M.rows() - 1);
  DynamicMatrix<double, columnMajor> beta = cov / var;

  // Expected returns
  DynamicMatrix<double, columnMajor> F(R.rows() - 1, 1, f);
  DynamicMatrix<double, columnMajor> out = F + beta * (M_mean - f);

  return as_doubles_matrix(out);
}
