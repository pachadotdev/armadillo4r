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
  
  result1 <- ols_traditional_(X, y)
  result2 <- ols_simplified_(X, y)
  result3 <- ols_simplified2_(X, y)
  result4 <- ols_simplified3_(X, y)
  
  expect_equal(result1, result2)
  expect_equal(result1, as.numeric(result3))
  expect_equal(result1, result4)
})

test_that("Matrix addition works", {
  A <- matrix(1:6, 2, 3)
  B <- matrix(7:12, 2, 3)
  
  result <- matrix_add_(A, B)
  expected <- A + B
  
  expect_equal(result, expected)
})

test_that("Integer matrix transpose works", {
  X <- matrix(1L:6L, 2, 3)
  
  result <- integer_transpose_(X)
  expected <- t(X)
  
  expect_equal(result, expected)
})

test_that("Unsigned integer matrix works", {
  X <- matrix(1L:6L, 2, 3)
  
  result <- uvec_example_(X)
  expected <- X + 1L
  
  expect_equal(result, expected)
})

test_that("Float matrix conversion works", {
  X <- matrix(1:6, 2, 3)
  
  result <- fmat_example_(X)
  expected <- X * 2
  
  expect_equal(result, expected)
})

test_that("Complex matrix multiplication works", {
  A <- matrix(complex(real = 1:4, imaginary = 1:4), 2, 2)
  B <- matrix(complex(real = 5:8, imaginary = 5:8), 2, 2)
  
  result <- complex_multiply_(A, B)
  expected <- A %*% B
  
  expect_equal(result, expected)
})

test_that("Generic element-wise multiplication works", {
  A <- matrix(1:6, 2, 3)
  B <- matrix(7:12, 2, 3)
  
  result <- generic_multiply_(A, B)
  expected <- A * B
  
  expect_equal(result, expected)
})
