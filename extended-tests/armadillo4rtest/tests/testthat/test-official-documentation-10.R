test_that("official documentation - 10", {
  set.seed(123)
  X <- matrix(rnorm(25), 5, 5)
  Y <- matrix(rnorm(25), 5, 5)

  res201 <- qz1_(X, Y, "none")
  expect_type(res201, "list")

  res202 <- schur1_(X)
  expect_type(res202, "list")

  res203 <- solve1_(X, Y)
  expect_type(res203, "double")

  res204 <- svd1_(X)
  U <- res204[[2]]
  S <- diag(res204[[3]])
  V <- res204[[4]]
  expect_type(res204, "list")
  expect_equal(U %*% S %*% t(V), X)

  res205 <- svd_econ1_(X)
  U <- res205[[1]]
  S <- diag(res205[[2]])
  V <- res205[[3]]
  expect_type(res205, "list")
  expect_equal(U %*% S %*% t(V), X)

  set.seed(123)
  A <- matrix(rnorm(25), 5, 5)
  B <- matrix(rnorm(25), 5, 5)
  C <- matrix(rnorm(25), 5, 5)
  res206 <- syl1_(A, B, C)
  expect_type(res206, "double")

  res207 <- eig_sym2_(A, "lm", 3)
  expect_type(res207, "list")

  res208 <- eig_gen2_(A, "lm", 2)
  expect_type(res208, "list")

  res209 <- svds1_(A, 2)
  expect_type(res209, "list")

  set.seed(123)
  b <- rnorm(5)
  res210 <- spsolve1_(A, b, "lapack")
})
