test_that("cpp11blaze vs base R (sorted)", {
  x <- mtcars_mat$x
  y <- mtcars_mat$y

  x <- x[, c("wt", "cyl4", "cyl6", "cyl8")]

  x <- cor(x)

  # blaze computation
  a <- sort(eigen_sym_mat_no_wrapper(x))
  
  b <- eigen_sym_dbl_no_wrapper(x)

  c <- eigen_gen_mat_no_wrapper(x)
  c_real <- sort(c$real)
  c_imag <- sort(c$imag)

  d <- eigen_gen_dbl_no_wrapper(x)
  d_real <- sort(d$real)
  d_imag <- sort(d$imag)

  # Base R computation
  e <- sort(eigen(x)$values)

  expect_equal(a, e)
  expect_equal(b, e)
  expect_equal(c_real, e)
  expect_equal(c_imag, rep(0, length(c_imag)))
  expect_equal(d_real, e)
  expect_equal(d_imag, rep(0, length(d_imag)))

  # the same but using the wrapper

  b <- eigen_gen_mat_complex_wrapper(x)
  b_real <- sort(b$real)
  b_imag <- sort(b$imag)

  c <- eigen_gen_dbl_complex_wrapper(x)
  c_real <- sort(c$real)
  c_imag <- sort(c$imag)

  d <- eigen_gen_dbl_no_wrapper(x)

  expect_equal(b_real, e)
  expect_equal(b_imag, rep(0, length(b_imag)))
  expect_equal(c_real, e)
  expect_equal(c_imag, rep(0, length(c_imag)))

  # case where the imaginary part is not zero

  x <- matrix(c(4/5, 3/5, 1, -3/5, 4/5, 2, 0, 0, 2), 3, 3)

  a <- eigen_gen_mat_complex_wrapper(x)

  b <- c()
  for (i in 1:3) {
    b[i] <- complex(real = a$real[i], imaginary = a$imag[i])
  }
  b <- sort(b)

  c <- sort(eigen(x)$values)

  expect_equal(b, c)
})
