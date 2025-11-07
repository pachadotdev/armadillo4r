test_that("OLS traditional approach works", {
  set.seed(123)
  n <- 100
  X <- matrix(rnorm(n * 3), n, 3)
  y <- rnorm(n)
  
  result <- ols_traditional_(X, y)
  expect_true(is.numeric(result))
  expect_equal(length(result), 3)
})

test_that("OLS with as_arma helper works", {
  set.seed(123)
  n <- 100
  X <- matrix(rnorm(n * 3), n, 3)
  y <- rnorm(n)
  
  result <- ols_helper_(X, y)
  expect_true(is.numeric(result))
  expect_equal(length(result), 3)
})

test_that("OLS with wrapper classes works", {
  set.seed(123)
  n <- 100
  X <- matrix(rnorm(n * 3), n, 3)
  y <- rnorm(n)
  
  result <- ols_wrapper_(X, y)
  expect_true(is.numeric(result))
  expect_equal(length(result), 3)
})

test_that("All three OLS approaches give same results", {
  set.seed(123)
  n <- 100
  X <- matrix(rnorm(n * 3), n, 3)
  y <- rnorm(n)
  
  result1 <- ols_traditional_(X, y)
  result2 <- ols_helper_(X, y)
  result3 <- ols_wrapper_(X, y)
  
  expect_equal(result1, result2)
  expect_equal(result2, result3)
})

test_that("Matrix addition with helper works", {
  A <- matrix(1:6, 2, 3)
  B <- matrix(7:12, 2, 3)
  
  result <- matrix_add_helper_(A, B)
  expected <- A + B
  
  expect_equal(result, expected)
})

test_that("Matrix addition with wrapper works", {
  A <- matrix(1:6, 2, 3)
  B <- matrix(7:12, 2, 3)
  
  result <- matrix_add_wrapper_(A, B)
  expected <- A + B
  
  expect_equal(result, expected)
})

test_that("Integer matrix transpose works", {
  X <- matrix(1L:6L, 2, 3)
  
  result <- integer_transpose_(X)
  expected <- t(X)
  
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
