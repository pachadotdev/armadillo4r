# OLS

test_that("OLS traditional approach works", {
  set.seed(123)
  n <- 100
  X <- matrix(rnorm(n * 3), n, 3)
  y <- rnorm(n)
  
  result <- ols_traditional_(X, y)
  expect_true(is.numeric(result))
  expect_equal(length(result), 3)
})

test_that("OLS simplified approach works", {
  set.seed(123)
  n <- 100
  X <- matrix(rnorm(n * 3), n, 3)
  y <- rnorm(n)
  
  result <- ols_simplified_(X, y)
  expect_true(is.numeric(result))
  expect_equal(length(result), 3)

  result <- ols_simplified2_(X, y)
  expect_true(is.matrix(result))
  expect_equal(nrow(result), 3)

  result <- ols_simplified3_(X, y)
  expect_true(is.numeric(result))
  expect_equal(length(result), 3)
})

test_that("All OLS approaches give same results", {
  set.seed(123)
  n <- 100
  X <- matrix(rnorm(n * 3), n, 3)
  y <- rnorm(n)
  
  result <- ols_traditional_(X, y)

  result1 <- ols_simplified_(X, y)
  result2 <- ols_simplified2_(X, y)
  result3 <- ols_simplified3_(X, y)
  result4 <- ols_simplified4_(X, y)
  result5 <- ols_simplified5_(X, y) # uses doubles and ignores the matrix output
  
  expect_equal(result, result1)
  expect_equal(result, as.numeric(result2))
  expect_equal(result, result3)
  expect_equal(result, result4)
  expect_equal(result, result5)
})

# Matrix operations

test_that("Matrix addition works with a strict type", {
  A <- matrix(1:6, 2, 3)
  B <- matrix(7:12, 2, 3)
  
  expect_error(matrix_add_(A, B))

  storage.mode(A) <- "numeric"
  storage.mode(B) <- "numeric"
  C <- A + B
  
  expect_equal(matrix_add_(A, B), C)
})

test_that("Matrix transpose works with a strict type", {
  X <- matrix(1L:6L, 2, 3)
  
  result <- integer_transpose_(X)
  expected <- t(X)
  
  expect_equal(result, expected)

  storage.mode(X) <- "numeric"
  expect_error(integer_transpose_(X))
})

test_that("Unsigned integer matrix works with a strict type", {
  X <- matrix(1L:6L, 2, 3)
  
  result <- uvec_example_(X)
  expected <- X + 1L
  
  expect_equal(result, expected)

  storage.mode(X) <- "numeric"
  expect_error(uvec_example_(X))
})

test_that("Float matrix conversion works", {
  X <- matrix(1:6, 2, 3)
  
  expect_error(fmat_example_(X))

  storage.mode(X) <- "numeric"
  result <- fmat_example_(X)
  expected <- X * 2
  
  expect_equal(result, expected)
})
