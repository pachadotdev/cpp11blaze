# Creation, transposition, deformation of an NxN matrix ----

#' @export 
matrix_calculation_01_r <- function(n) {
  a <- matrix(rnorm(n * n) / 10, ncol = n, nrow = n)
  b <- t(a)
  dim(b) <- c(n/2, n*2)
  a <- t(b)
  return(0L)
}

# NxN normal distributed random matrix^1000 ----

#' @export
matrix_calculation_02_r <- function(n) {
  a <- abs(matrix(rnorm(n * n) / 2, ncol = n, nrow = n))
  b <- a^1000
  return(0L)
}

# Sorting of N random values ----

#' @export
matrix_calculation_03_r <- function(n) {
  a <- rnorm(n)
  b <- sort(a, method = "quick")
  return(0L)
}

# NxN cross-product matrix ----

#' @export
matrix_calculation_04_r <- function(n) {
  a <- matrix(rnorm(n * n), ncol = n, nrow = n)
  b <- crossprod(a)
  return(0L)
}

# Linear regression over an NxN matrix via QR decomposition ----

#' @export
matrix_calculation_05_r <- function(n) {
  # same as lm() for full rank matrices but in Armadillo there is no lm()
  # equivalent
  x <- matrix(rnorm(n * n), ncol = n, nrow = n)
  y <- rnorm(n)
  b <- qr.solve(x, y)
  return(0L)
}
