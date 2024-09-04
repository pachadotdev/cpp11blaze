test_that("Cholesky decomposition 1", {
  set.seed(200100)
  x <- matrix(runif(25, 0, 1), nrow = 5, ncol = 5)
  x <- t(x) %*% x
  y <- chol_mat(x)

  expect_true(all(y[upper.tri(y)] == 0))

  expect_true(all.equal(x, y %*% t(y)))
})
