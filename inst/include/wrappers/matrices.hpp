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
inline blaze::DynamicMatrix<T, blaze::columnMajor> dblint_matrix_to_DynamicMatrix_(
    const U& x) {
  const size_t n = x.nrow();
  const size_t m = x.ncol();

  if (std::is_same<U, doubles_matrix<>>::value) {
    blaze::CustomMatrix<T, blaze::unaligned, blaze::unpadded, blaze::columnMajor> y(
        reinterpret_cast<T*>(REAL(x.data())), n, m);
    return y;
  } else {
    blaze::CustomMatrix<T, blaze::unaligned, blaze::unpadded, blaze::columnMajor> y(
        reinterpret_cast<T*>(INTEGER(x.data())), n, m);
    return y;
  }
}

template <typename T, typename U>
inline blaze::DynamicMatrix<T, blaze::columnMajor> dblint_to_DynamicMatrix_(const U& x) {
  const size_t n = x.size();

  if (std::is_same<U, doubles>::value) {
    blaze::CustomMatrix<T, blaze::unaligned, blaze::unpadded, blaze::columnMajor> y(
        reinterpret_cast<T*>(REAL(x.data())), n, 1);
    return y;
  } else {
    blaze::CustomMatrix<T, blaze::unaligned, blaze::unpadded, blaze::columnMajor> y(
        reinterpret_cast<T*>(INTEGER(x.data())), n, 1);
    return y;
  }
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
  const size_t n = A.rows();
  const size_t m = A.columns();

  using dblint_matrix =
      typename std::conditional<std::is_same<U, doubles_matrix<>>::value,
                                writable::doubles_matrix<>,
                                writable::integers_matrix<>>::type;

  dblint_matrix B(n, m);

  if (std::is_same<U, doubles_matrix<>>::value) {
    double* B_data = REAL(B);

#ifdef _OPENMP
#pragma omp parallel for schedule(static) collapse(2)
#endif
    for (size_t j = 0; j < m; ++j) {
      for (size_t i = 0; i < n; ++i) {
        B_data[i + n * j] = A(i, j);
      }
    }
  } else {
    int* B_data = INTEGER(B);

#ifdef _OPENMP
#pragma omp parallel for schedule(static) collapse(2)
#endif
    for (size_t j = 0; j < m; ++j) {
      for (size_t i = 0; i < n; ++i) {
        B_data[i + n * j] = A(i, j);
      }
    }
  }

  // I tried this but it returns disorganized matrices
  // example:
  // [ 1 0 0 ]
  // [ 2 3 0 ]
  // [ 4 5 6 ]
  // becomes
  // [ 1 0 3 ]
  // [ 2 0 6 ]
  // [ 4 5 0 ]

  // if (std::is_same<U, doubles_matrix<>>::value) {
  //   double* B_data = REAL(B);
  //   // std::copy(A.data(), A.data() + n * m, B_data);
  //   std::memcpy(B_data, A.data(), n * m * sizeof(double));
  // } else {
  //   int* B_data = INTEGER(B);
  //   std::memcpy(B_data, A.data(), n * m * sizeof(int));
  //   // std::copy(A.data(), A.data() + n * m, B_data);
  // }

  return B;
}

template <typename T, typename U>
inline U DynamicMatrix_to_dblint_(const blaze::DynamicMatrix<T, blaze::columnMajor>& A) {
  const size_t n = A.rows();
  const size_t m = A.columns();

  if (m != 1) {
    throw std::runtime_error("Matrix must have only one column");
  }

  using dblint = typename std::conditional<std::is_same<U, doubles>::value,
                                           writable::doubles, writable::integers>::type;

  dblint B(n);

  if (std::is_same<U, doubles>::value) {
    double* B_data = REAL(B);
    std::memcpy(B_data, A.data(), n * sizeof(double));
  } else {
    int* B_data = INTEGER(B);
    std::memcpy(B_data, A.data(), n * sizeof(int));
  }

  return B;
}

inline doubles_matrix<> as_doubles_matrix(
    const blaze::DynamicMatrix<double, blaze::columnMajor>& A) {
  return DynamicMatrix_to_dblint_matrix_<double, doubles_matrix<>>(A);
}

inline integers_matrix<> as_integers_matrix(
    const blaze::DynamicMatrix<int, blaze::columnMajor>& A) {
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
  blaze::DynamicMatrix<double, blaze::columnMajor> A_real(n, m);
  blaze::DynamicMatrix<double, blaze::columnMajor> A_imag(n, m);

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

inline list as_complex_matrix(
    const blaze::DynamicMatrix<std::complex<double>, blaze::columnMajor>& A) {
  return DynamicMatrix_to_complex_matrix_<std::complex<double>>(A);
}

#endif
