#include <fftw3.h>
#include <algorithm>
#include <cpp11.hpp>
#include <cpp11blaze.hpp>
#include <random>

using namespace blaze;
using namespace cpp11;

// headers for own functions

std::mt19937& random_normal();

blaze::DynamicMatrix<double> cor(const blaze::DynamicMatrix<double>& x);

blaze::DynamicMatrix<double, blaze::columnMajor> hstack(
    const blaze::DynamicMatrix<double, blaze::columnMajor>& A,
    const blaze::DynamicMatrix<double, blaze::columnMajor>& B);
