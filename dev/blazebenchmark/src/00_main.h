#include <fftw3.h>
#include <algorithm>
#include <cpp11.hpp>
#include <cpp11blaze.hpp>
#include <random>

using namespace blaze;
using namespace cpp11;

// headers for own functions

std::mt19937& random_normal();

template <typename T>
DynamicVector<T, columnVector> linspace(T start, T end, std::size_t num);

DynamicMatrix<double> cor(const DynamicMatrix<double>& x);

DynamicMatrix<double> hstack(const DynamicMatrix<double>& A,
                             const DynamicMatrix<double>& B);
