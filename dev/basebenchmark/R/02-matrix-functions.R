# FFT over N random values ----

#' @export
matrix_functions_01_r <- function(n) {
  a <- rnorm(n)
  b <- fft(a)
  return(0L)
}

# Eigenvalues of an NxX random matrix ----

#' @export
matrix_functions_02_r <- function(n) {
  a <- matrix(rnorm(n * n), ncol = n, nrow = n)
  b <- eigen(a, symmetric = FALSE, only.values = TRUE)$values
  return(0L)
}

# Determinant of an NxN random matrix ----

#' @export
matrix_functions_03_r <- function(n) {
  a <- matrix(rnorm(n * n), ncol = n, nrow = n)
  b <- det(a)
  return(0L)
}

# Cholesky decomposition of an NxN matrix ----

#' @export
matrix_functions_04_r <- function(n) {
  a <- crossprod(matrix(rnorm(n * n), ncol = n, nrow = n))
  b <- chol(a)
  return(0L)
}

# Inverse of an NxN random matrix ----

#' @export
matrix_functions_05_r <- function(n) {
  a <- matrix(rnorm(n * n), ncol = n, nrow = n)
  b <- solve(a)
  return(0L)
}
