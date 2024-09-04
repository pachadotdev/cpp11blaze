// cpp11eigen version: 0.2.0
// vendored on: 2024-09-02
#pragma once

using namespace cpp11;

#ifndef MATRICES_HPP
#define MATRICES_HPP

////////////////////////////////////////////////////////////////
// R to Eigen
////////////////////////////////////////////////////////////////

template <typename T>
inline Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> as_Matrix(const T& x) {
  // Generic implementation
  throw std::runtime_error("Cannot convert to Mat");
}

template <typename T, typename U>
inline Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> dblint_matrix_to_Matrix_(
    const U& x) {
  const int n = x.nrow();
  const int m = x.ncol();

  if (std::is_same<U, doubles_matrix<>>::value) {
    Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> y(
        reinterpret_cast<T*>(REAL(x.data())), n, m);
    return y;
  } else {
    Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> y(
        reinterpret_cast<T*>(INTEGER(x.data())), n, m);
    return y;
  }
}

template <typename T, typename U>
inline Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> dblint_to_Matrix_(const U& x) {
  const int n = x.size();

  if (std::is_same<U, doubles>::value) {
    Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> y(
        reinterpret_cast<T*>(REAL(x.data())), n, 1);
    return y;
  } else {
    Eigen::Map<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> y(
        reinterpret_cast<T*>(INTEGER(x.data())), n, 1);
    return y;
  }
}

inline Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> as_Matrix(
    const doubles_matrix<>& x) {
  return dblint_matrix_to_Matrix_<double, doubles_matrix<>>(x);
}

inline Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> as_Matrix(
    const integers_matrix<>& x) {
  return dblint_matrix_to_Matrix_<int, integers_matrix<>>(x);
}

inline Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> as_Matrix(const doubles& x) {
  return dblint_to_Matrix_<double, doubles>(x);
}

inline Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> as_Matrix(const integers& x) {
  return dblint_to_Matrix_<int, integers>(x);
}

////////////////////////////////////////////////////////////////
// Eigen to R
////////////////////////////////////////////////////////////////

// Double/Integer

template <typename T, typename U>
inline U Matrix_to_dblint_matrix_(
    const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& A) {
  const int n = A.rows();
  const int m = A.cols();

  using dblint_matrix =
      typename std::conditional<std::is_same<U, doubles_matrix<>>::value,
                                writable::doubles_matrix<>,
                                writable::integers_matrix<>>::type;

  dblint_matrix B(n, m);

#ifdef _OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      B(i, j) = A(i, j);
    }
  }

  return B;
}

inline doubles_matrix<> as_doubles_matrix(
    const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& A) {
  return Matrix_to_dblint_matrix_<double, doubles_matrix<>>(A);
}

inline integers_matrix<> as_integers_matrix(
    const Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic>& A) {
  return Matrix_to_dblint_matrix_<int, integers_matrix<>>(A);
}

// Complex

template <typename T>
inline list Matrix_to_complex_matrix_(
    const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& A) {
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> A_real = A.real();
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> A_imag = A.imag();

  writable::list B;
  B.push_back({"real"_nm = as_doubles_matrix(A_real)});
  B.push_back({"imag"_nm = as_doubles_matrix(A_imag)});

  return B;
}

inline list as_complex_matrix(
    const Eigen::Matrix<std::complex<double>, Eigen::Dynamic, Eigen::Dynamic>& A) {
  return Matrix_to_complex_matrix_<std::complex<double>>(A);
}

#endif
