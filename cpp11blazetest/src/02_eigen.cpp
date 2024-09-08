#include "00_main.h"

// Symmetric case

DynamicVector<double, columnVector> eigen_sym_(const doubles_matrix<>& x) {
  SymmetricMatrix<DynamicMatrix<double, columnMajor>> X = as_DynamicMatrix(x);
  DynamicVector<double, columnVector> eigenvalues;
  eigen(X, eigenvalues);
  return eigenvalues;
}

[[cpp11::register]] doubles_matrix<> eigen_sym_mat_no_wrapper(const doubles_matrix<>& x) {
  DynamicVector<double, columnVector> y = eigen_sym_(x);
  return as_doubles_matrix(y);
}

[[cpp11::register]] doubles eigen_sym_dbl_no_wrapper(const doubles_matrix<>& x) {
  DynamicVector<double, columnVector> y = eigen_sym_(x);
  return as_doubles(y);
}

// General case

DynamicVector<std::complex<double>, columnVector> eigen_gen_(const doubles_matrix<>& x) {
  DynamicMatrix<double, columnMajor> X = as_DynamicMatrix(x);
  DynamicVector<std::complex<double>, columnVector> eigenvalues;
  geev(X, eigenvalues);
  return eigenvalues;
}

[[cpp11::register]] list eigen_gen_mat_complex_wrapper(const doubles_matrix<>& x) {
  DynamicVector<std::complex<double>, columnVector> y = eigen_gen_(x);
  return as_complex_matrix(y);
}

[[cpp11::register]] list eigen_gen_dbl_complex_wrapper(const doubles_matrix<>& x) {
  DynamicVector<std::complex<double>, columnVector> y = eigen_gen_(x);
  return as_complex_doubles(y);
}

[[cpp11::register]] list eigen_gen_mat_no_wrapper(const doubles_matrix<>& x) {
  DynamicVector<std::complex<double>, columnVector> y = eigen_gen_(x);

  const size_t n = y.size();
  DynamicVector<double, columnVector> y_real(n);
  DynamicVector<double, columnVector> y_imag(n);

  for (size_t i = 0; i < n; ++i) {
    y_real[i] = y[i].real();
    y_imag[i] = y[i].imag();
  }

  writable::list out;
  out.push_back({"real"_nm = as_doubles_matrix(y_real)});
  out.push_back({"imag"_nm = as_doubles_matrix(y_imag)});

  return out;
}

[[cpp11::register]] list eigen_gen_dbl_no_wrapper(const doubles_matrix<>& x) {
  DynamicVector<std::complex<double>, columnVector> y = eigen_gen_(x);

  const size_t n = y.size();
  DynamicVector<double, columnVector> y_real(n);
  DynamicVector<double, columnVector> y_imag(n);

  for (size_t i = 0; i < n; ++i) {
    y_real[i] = y[i].real();
    y_imag[i] = y[i].imag();
  }

  writable::list out;
  out.push_back({"real"_nm = as_doubles(y_real)});
  out.push_back({"imag"_nm = as_doubles(y_imag)});

  return out;
}
