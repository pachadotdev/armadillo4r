source(system.file("tinytest", "helper-sparse.R", package = "armadillo4rtest"))

local({
  set.seed(123)
  X <- matrix(rnorm(25), 5, 5)
  Y <- matrix(rnorm(25), 5, 5)

  res201 <- qz1_(X, Y, "none")
  expect_true(is.list(res201))

  res202 <- schur1_(X)
  expect_true(is.list(res202))

  res203 <- solve1_(X, Y)
  expect_true(is.double(res203))

  res204 <- svd1_(X)
  U <- res204[[2]]
  S <- diag(res204[[3]])
  V <- res204[[4]]
  expect_true(is.list(res204))
  expect_equal(U %*% S %*% t(V), X)

  res205 <- svd_econ1_(X)
  U <- res205[[1]]
  S <- diag(res205[[2]])
  V <- res205[[3]]
  expect_true(is.list(res205))
  expect_equal(U %*% S %*% t(V), X)

  set.seed(123)
  A <- matrix(rnorm(25), 5, 5)
  B <- matrix(rnorm(25), 5, 5)
  C <- matrix(rnorm(25), 5, 5)
  res206 <- syl1_(A, B, C)
  expect_true(is.double(res206))
})

# official documentation - 10 (sparse)
local({
  if (!skip_if_no_sparse()) return(invisible(NULL))

  set.seed(123)
  A <- matrix(rnorm(25), 5, 5)
  
  res207 <- eig_sym2_(A, "lm", 3)
  expect_true(is.list(res207))

  res208 <- eig_gen2_(A, "lm", 2)
  expect_true(is.list(res208))

  res209 <- svds1_(A, 2)
  expect_true(is.list(res209))

  set.seed(123)
  b <- rnorm(5)
  res210 <- spsolve1_(A, b, "lapack")
})
