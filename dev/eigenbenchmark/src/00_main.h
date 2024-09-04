// this pragma keeps the output minimal and eases finding the relevant warnings
// or errors
#pragma GCC diagnostic ignored "-Wignored-attributes"

// add extra Eigen headers here
// cpp11eigen.hpp only includes eigen/Dense
// #include <eigen/Eigenvalues>
// #include <eigen/Cholesky>

#include <cpp11.hpp>
#include <cpp11eigen.hpp>
#include <random>
#include <unsupported/Eigen/FFT>

using namespace Eigen;
using namespace cpp11;

std::mt19937& random_normal();
