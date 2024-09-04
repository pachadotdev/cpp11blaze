#pragma once

using namespace cpp11;

#ifndef VECTORS_HPP
#define VECTORS_HPP

// Note: dblint = doubles or integers

////////////////////////////////////////////////////////////////
// R to Blaze
////////////////////////////////////////////////////////////////

// vector or doubles/integers to DynamicVector

template <typename T>
inline blaze::DynamicVector<T, blaze::columnVector> as_DynamicVector(const T& x) {
  // Generic implementation
  throw std::runtime_error("Cannot convert to Col");
}

template <typename T, typename U>
inline blaze::DynamicVector<T, blaze::columnVector> as_DynamicVector_(const U& x) {
  const size_t n = x.size();

  blaze::DynamicVector<T, blaze::columnVector> y(n);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (size_t i = 0; i < n; ++i) {
    y[i] = x[i];
  }

  return y;
}

inline blaze::DynamicVector<double, blaze::columnVector> as_DynamicVector(
    const doubles& x) {
  return as_DynamicVector_<double, doubles>(x);
}

inline blaze::DynamicVector<int, blaze::columnVector> as_DynamicVector(
    const integers& x) {
  return as_DynamicVector_<int, integers>(x);
}

////////////////////////////////////////////////////////////////
// Blaze to R
////////////////////////////////////////////////////////////////

// Double/Integer to vector

template <typename T, typename U>
inline U DynamicVector_to_dblint_(const blaze::DynamicVector<T, blaze::columnVector>& x) {
  const size_t n = x.size();

  using dblint = typename std::conditional<std::is_same<U, doubles>::value,
                                           writable::doubles, writable::integers>::type;

  dblint y(n);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (size_t i = 0; i < n; ++i) {
    y[i] = x[i];
  }

  return y;
}

inline integers as_integers(const blaze::DynamicVector<int, blaze::columnVector>& x) {
  return DynamicVector_to_dblint_<int, integers>(x);
}

inline doubles as_doubles(const blaze::DynamicVector<double, blaze::columnVector>& x) {
  return DynamicVector_to_dblint_<double, doubles>(x);
}

// same as above, but for matrices

template <typename T, typename U>
inline U DynamicVector_to_dblint_matrix_(
    const blaze::DynamicVector<T, blaze::columnVector>& x) {
  const int n = x.size();
  const int m = 1;

  using dblint_matrix =
      typename std::conditional<std::is_same<U, doubles_matrix<>>::value,
                                writable::doubles_matrix<>,
                                writable::integers_matrix<>>::type;

  dblint_matrix y(n, m);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (int i = 0; i < n; ++i) {
    y(i, 0) = x[i];
  }

  return y;
}

inline doubles_matrix<> as_doubles_matrix(
    const blaze::DynamicVector<double, blaze::columnVector>& x) {
  return DynamicVector_to_dblint_matrix_<double, doubles_matrix<>>(x);
}

inline integers_matrix<> as_integers_matrix(
    const blaze::DynamicVector<int, blaze::columnVector>& x) {
  return DynamicVector_to_dblint_matrix_<int, integers_matrix<>>(x);
}

// Complex

inline list as_complex_doubles(const blaze::DynamicVector<std::complex<double>, blaze::columnVector>& x) {
  const size_t n = x.size();
  blaze::DynamicVector<double, blaze::columnVector> x_real(n);
  blaze::DynamicVector<double, blaze::columnVector> x_imag(n);

  for (size_t i = 0; i < n; ++i) {
    x_real[i] = x[i].real();
    x_imag[i] = x[i].imag();
  }

  return writable::list({"real"_nm = as_doubles(x_real), "imag"_nm = as_doubles(x_imag)});
}

inline list as_complex_matrix(const blaze::DynamicVector<std::complex<double>, blaze::columnVector>& x) {
  const size_t n = x.size();
  blaze::DynamicVector<double, blaze::columnVector> x_real(n);
  blaze::DynamicVector<double, blaze::columnVector> x_imag(n);

  for (size_t i = 0; i < n; ++i) {
    x_real[i] = x[i].real();
    x_imag[i] = x[i].imag();
  }

  return writable::list(
      {"real"_nm = as_doubles_matrix(x_real), "imag"_nm = as_doubles_matrix(x_imag)});
}

#endif
