# N Fibonacci numbers calculation (vector calc) ----

#' @export
programmation_01_r <- function(n) {
  phi <- 1.6180339887498949
  a <- floor(runif(n) * 1000)
  b <- (phi^a - (-phi)^(-a)) / sqrt(5)
  return(0L)
}

# Creation of an NxN Hilbert matrix ----

#' @export
programmation_02_r <- function(n) {
  a <- outer(0:(n - 1), 0:(n - 1), function(i, j) 1 / (i + j + 1))
  return(0L)
}

# Grand common divisors of N pairs ----

gcd <- function(a, b) {
  if (b == 0) {
    return(a)
  } else {
    return(gcd(b, a %% b))
  }
}

#' @export
programmation_03_r <- function(n) {
  a <- ceiling(runif(n) * 1000)
  b <- ceiling(runif(n) * 1000)
  c <- mapply(gcd, a, b) # gcd is a recursive function
  return(0L)
}

# Creation of an NxN Toeplitz matrix ----

#' @export
programmation_04_r <- function(n) {
  b <- outer(1:n, 1:n, function(j, k) abs(j - k) + 1)
  return(0L)
}

# Escoufier's method on a NxX matrix ----

#' @export
programmation_05_r <- function(n) {
  x <- matrix(abs(rnorm(n * n)), nrow = n, ncol = n)
  vt <- 1:n # Variables to test
  vr <- numeric(n) # Result: ordered variables
  RV <- numeric(n) # Result: correlations

  for (j in 1:n) { # loop on the variable number
    Rvmax <- 0
    vrt <- NULL
    for (k in 1:(n - j + 1)) { # loop on the variables
      x2 <- cbind(x, x[, vr[1:(j - 1)]], x[, vt[k]])
      R <- cor(x2) # Correlations table
      Ryy <- R[1:n, 1:n]
      Rxx <- R[(n + 1):(n + j), (n + 1):(n + j)]
      Rxy <- R[(n + 1):(n + j), 1:n]
      Ryx <- t(Rxy)
      trace_Ryx_Rxy <- sum(diag(Ryx %*% Rxy))
      trace_Ryy_Ryy <- sum(diag(Ryy %*% Ryy))
      trace_Rxx_Rxx <- sum(diag(Rxx %*% Rxx))
      rvt <- trace_Ryx_Rxy / sqrt(trace_Ryy_Ryy * trace_Rxx_Rxx) # RV calculation
      if (rvt > Rvmax) {
        Rvmax <- rvt # test of RV
        vrt <- vt[k] # temporary held variable
      }
    }
    vr[j] <- vrt # Result: variable
    RV[j] <- Rvmax # Result: correlation
    vt <- vt[vt != vrt] # reidentify variables to test
  }
  return(0L)
}
