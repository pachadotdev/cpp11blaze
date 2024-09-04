// cpp11eigen version: 0.2.0
// vendored on: 2024-09-02
#pragma once

using namespace cpp11;

#ifndef VECTORS_HPP
#define VECTORS_HPP

// Note: dblint = doubles or integers

////////////////////////////////////////////////////////////////
// Eigen to R
////////////////////////////////////////////////////////////////

// Double/Integer to vector

template <typename T, typename U>
inline U Matrix_to_dblint_(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& x) {
  const int n = x.rows();
  const int m = x.cols();

  if (m != 1) {
    throw std::runtime_error("Only column vectors can be converted to doubles/integers");
  }

  using dblint = typename std::conditional<std::is_same<U, doubles>::value,
                                           writable::doubles, writable::integers>::type;

  dblint y(n);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    y[i] = x(i, 0);
  }

  return y;
}

inline integers as_integers(const Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic>& x) {
  return Matrix_to_dblint_<int, integers>(x);
}

inline doubles as_doubles(
    const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& x) {
  return Matrix_to_dblint_<double, doubles>(x);
}

// Complex to vector

template <typename T>
inline list Matrix_to_complex_dbl_(
    const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& A) {
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> A_real = A.real();
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> A_imag = A.imag();

  writable::list B;
  B.push_back({"real"_nm = as_doubles(A_real)});
  B.push_back({"imag"_nm = as_doubles(A_imag)});

  return B;
}

inline list as_complex_doubles(
    const Eigen::Matrix<std::complex<double>, Eigen::Dynamic, Eigen::Dynamic>& A) {
  return Matrix_to_complex_dbl_<std::complex<double>>(A);
}

#endif
