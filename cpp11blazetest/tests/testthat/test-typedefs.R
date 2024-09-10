test_that("elemental tests for vectors", {
  x <- c(1.0, 2.0, 3.0)
  expect_equal(x, typedef_Col_double(x))

  x[1] <- NA
  expect_equal(x, typedef_Col_double(x))

  x[1] <- NaN
  expect_equal(x, typedef_Col_double(x))

  x[1] <- Inf
  expect_equal(x, typedef_Col_double(x))

  x[1] <- -Inf
  expect_equal(x, typedef_Col_double(x))
  
  y <- c(1L, 2L, 3L)
  expect_equal(y, typedef_Col_int(y))

  y[1] <- NA
  expect_equal(y, typedef_Col_int(y))

  y[1] <- NaN
  expect_error(typedef_Col_int(y), "expected 'integer' actual 'double'")

  y[1] <- Inf
  expect_error(typedef_Col_int(y), "expected 'integer' actual 'double'")

  y[1] <- -Inf
  expect_error(typedef_Col_int(y), "expected 'integer' actual 'double'")
})

test_that("elemental tests for matrices", {
  set.seed(1234)
  x <- matrix(rnorm(4), nrow = 2)
  expect_equal(x, typedef_Mat_double(x))

  x[1,1] <- NA
  expect_equal(x, typedef_Mat_double(x))

  x[1,1] <- NaN
  expect_equal(x, typedef_Mat_double(x))

  x[1,1] <- Inf
  expect_equal(x, typedef_Mat_double(x))

  x[1,1] <- -Inf
  expect_equal(x, typedef_Mat_double(x))

  y <- matrix(rpois(4,1), nrow = 2)
  expect_equal(y, typedef_Mat_int(y))

  y[1,1] <- NA
  expect_equal(y, typedef_Mat_int(y))

  y[1,1] <- NaN
  expect_error(typedef_Mat_int(y), "expected 'integer' actual 'double'")

  y[1,1] <- Inf
  expect_error(typedef_Mat_int(y), "expected 'integer' actual 'double'")

  y[1,1] <- -Inf
  expect_error(typedef_Mat_int(y), "expected 'integer' actual 'double'")
})
