# elemental tests for vectors ----

local({
  x <- c(1.0, 2.0, 3.0)
  expect_equal(x, typedef_Col_double(x))

  x[1] <- NA
  expect_equal(x, typedef_Col_double(x))

  x[1] <- 1.0
  x[2] <- Inf
  expect_equal(x, typedef_Col_double(x))

  x[2] <- -Inf
  expect_equal(x, typedef_Col_double(x))

  x[2] <- NaN
  expect_equal(x, typedef_Col_double(x))

  y <- c(1L, 2L, 3L)
  expect_equal(y, typedef_Col_int(y))

  y[3] <- NA
  expect_equal(y, typedef_Col_int(y))

  y[3] <- Inf
  # class(y) is numeric now!
  expect_error(typedef_Col_int(y), "expected 'integer' actual 'double'")

  y[3] <- -Inf
  expect_error(typedef_Col_int(y), "expected 'integer' actual 'double'")

  y[3] <- NaN
  expect_error(typedef_Col_int(y), "expected 'integer' actual 'double'")

  y <- c(1L, 2L, 3L)
  expect_equal(y, typedef_uvec(y))

  y[1] <- -1L
  expect_equal(y, typedef_uvec(y))
})

# elemental tests for matrices ----

local({
  set.seed(1234)
  x <- matrix(rnorm(4), nrow = 2)
  expect_equal(x, typedef_Mat_double(x))

  y <- matrix(rpois(4, 1), nrow = 2)
  expect_equal(y, typedef_Mat_int(y))

  y[1, 1] <- NA
  expect_equal(y, typedef_Mat_int(y))

  y[1, 1] <- Inf
  expect_error(typedef_Mat_int(y))
  expect_equal(y, typedef_Mat_double(y))

  y[1, 1] <- -Inf
  expect_error(typedef_Mat_int(y))
  expect_equal(y, typedef_Mat_double(y))

  y[1, 1] <- NaN
  expect_equal(y, typedef_Mat_double(y))
})

# elemental tests for sparse matrices ----

local({
  if (!skip_if_no_sparse()) return(invisible(NULL))

  set.seed(1234)
  y <- matrix(rpois(4, 1), nrow = 2)
  diag(y) <- 0
  expect_equal(y, typedef_SpMat_double(y))

  storage.mode(y) <- "integer"
  expect_equal(y, typedef_SpMat_int(y))
})

# compatible casting for matrices ----
local({
  if (!skip_if_no_sparse()) return(invisible(NULL))

  set.seed(123)
  x <- round(matrix(rnorm(4), nrow = 2), 3)
  res <- typedef_dblmat_exchangeability(x)
  n <- length(res)
  for (i in seq_len(n - 1)) {
    expect_true(all.equal(res[[n]], res[[i]]))
  }
  
  set.seed(200100)
  y <- matrix(rbinom(25, 1, 0.5), 5, 5)
  storage.mode(y) <- "double"
  res <- typedef_spmat_exchangeability(y)
  n <- length(res)
  for (i in seq_len(n - 1)) {
    expect_true(all.equal(res[[n]], res[[i]]))
  }

  set.seed(200200)
  y <- matrix(rbinom(25, 1, 0.5), 5, 5)
  res <- typedef_spmat_int_exchangeability(y)
  n <- length(res)
  for (i in seq_len(n - 1)) {
    expect_true(all.equal(res[[n]], res[[i]]))
  }
})
