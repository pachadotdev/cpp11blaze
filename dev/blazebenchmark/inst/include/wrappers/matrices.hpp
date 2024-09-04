// cpp11blaze version: 0.2.0
// vendored on: 2024-09-03
#pragma once

using namespace cpp11;

#ifndef MATRICES_HPP
#define MATRICES_HPP

////////////////////////////////////////////////////////////////
// R to Blaze
////////////////////////////////////////////////////////////////

template <typename T>
inline blaze::DynamicMatrix<T, blaze::columnMajor> as_DynamicMatrix(const T& x) {
  // Generic implementation
  throw std::runtime_error("Cannot convert to Mat");
}

template <typename T, typename U>
inline blaze::DynamicMatrix<T, blaze::columnMajor> dblint_matrix_to_DynamicMatrix_(const U& x) {
  const size_t n = x.nrow();
  const size_t m = x.ncol();

  blaze::DynamicMatrix<T, blaze::columnMajor> y(n, m);

#ifdef _OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      y(i, j) = x(i, j);
    }
  }

  return y;
}

template <typename T, typename U>
inline blaze::DynamicMatrix<T, blaze::columnMajor> dblint_to_DynamicMatrix_(const U& x) {
  const size_t n = x.size();

  blaze::DynamicMatrix<T, blaze::columnMajor> y(n, 1);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (size_t i = 0; i < n; ++i) {
    y(i, 0) = x[i];
  }

  return y;
}

inline blaze::DynamicMatrix<double, blaze::columnMajor> as_DynamicMatrix(
    const doubles_matrix<>& x) {
  return dblint_matrix_to_DynamicMatrix_<double, doubles_matrix<>>(x);
}

inline blaze::DynamicMatrix<int, blaze::columnMajor> as_DynamicMatrix(
    const integers_matrix<>& x) {
  return dblint_matrix_to_DynamicMatrix_<int, integers_matrix<>>(x);
}

inline blaze::DynamicMatrix<double, blaze::columnMajor> as_DynamicMatrix(
    const doubles& x) {
  return dblint_to_DynamicMatrix_<double, doubles>(x);
}

inline blaze::DynamicMatrix<int, blaze::columnMajor> as_DynamicMatrix(const integers& x) {
  return dblint_to_DynamicMatrix_<int, integers>(x);
}

////////////////////////////////////////////////////////////////
// Blaze to R
////////////////////////////////////////////////////////////////

// Double/Integer

template <typename T, typename U>
inline U DynamicMatrix_to_dblint_matrix_(
    const blaze::DynamicMatrix<T, blaze::columnMajor>& A) {
  const int n = A.rows();
  const int m = A.columns();

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

template <typename T, typename U>
inline U DynamicMatrix_to_dblint_(const blaze::DynamicMatrix<T, blaze::columnMajor>& A) {
  const int n = A.rows();
  const int m = A.columns();

  if (m != 1) {
    throw std::runtime_error("Matrix must have only one column");
  }

  using dblint = typename std::conditional<std::is_same<U, doubles>::value,
                                           writable::doubles, writable::integers>::type;

  dblint B(n);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    B[i] = A(i, 0);
  }

  return B;
}

inline doubles_matrix<>
  as_doubles_matrix(const blaze::DynamicMatrix<double, blaze::columnMajor>& A) {
  return DynamicMatrix_to_dblint_matrix_<double, doubles_matrix<>>(A);
}

inline integers_matrix<> as_integers_matrix(const blaze::DynamicMatrix<int, blaze::columnMajor>& A) {
  return DynamicMatrix_to_dblint_matrix_<int, integers_matrix<>>(A);
}

inline doubles as_doubles(const blaze::DynamicMatrix<double, blaze::columnMajor>& A) {
  return DynamicMatrix_to_dblint_<double, doubles>(A);
}

inline integers as_integers(const blaze::DynamicMatrix<int, blaze::columnMajor>& A) {
  return DynamicMatrix_to_dblint_<int, integers>(A);
}

// Complex

template <typename T>
inline list DynamicMatrix_to_complex_matrix_(
    const blaze::DynamicMatrix<T, blaze::columnMajor>& A) {
  const size_t n = A.rows();
  const size_t m = A.columns();
  blaze::DynamicMatrix<double, blaze::columnVector> A_real(n, m);
  blaze::DynamicMatrix<double, blaze::columnVector> A_imag(n, m);

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      A_real(i, j) = A(i, j).real();
      A_imag(i, j) = A(i, j).imag();
    }
  }

  writable::list B;
  B.push_back({"real"_nm = as_doubles_matrix(A_real)});
  B.push_back({"imag"_nm = as_doubles_matrix(A_imag)});

  return B;
}

inline list as_complex_matrix(const blaze::DynamicMatrix<std::complex<double>, blaze::columnMajor>& A) {
  return DynamicMatrix_to_complex_matrix_<std::complex<double>>(A);
}

#endif
