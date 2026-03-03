# ------------------------------------------------------------------ #
# Tests for the conversion wrappers documented in converting.Rmd     #
# ------------------------------------------------------------------ #

# ------------------------------------------------------------------ #
# R to Armadillo: Matrices                                           #
# ------------------------------------------------------------------ #

test_that("mat_demo_: matrix conversions produce correct output", {
  x  <- matrix(c(1.5, 2.5, 3.5, 4.5), nrow = 2)
  xi <- matrix(1L:4L, nrow = 2)

  result <- mat_demo_(x, xi)

  # A * A' for a 2x2 matrix
  A        <- x
  expected <- A %*% t(A)

  expect_true(is.matrix(result))
  expect_equal(dim(result), c(2L, 2L))
  expect_equal(result, expected)
})

test_that("mat_demo_: accepts integer matrix for xi", {
  x  <- matrix(runif(9), nrow = 3)
  xi <- matrix(1L:9L, nrow = 3)
  expect_silent(mat_demo_(x, xi))
})

# ------------------------------------------------------------------ #
# R to Armadillo: Vectors                                            #
# ------------------------------------------------------------------ #

test_that("vec_demo_: element-wise square is correct", {
  y  <- c(1.0, 2.0, 3.0)
  yi <- 1L:3L

  result   <- vec_demo_(y, yi)
  expected <- y^2

  expect_true(is.numeric(result))
  expect_equal(result, expected)
})

test_that("vec_demo_: works for a single element", {
  expect_equal(vec_demo_(5.0, 1L), 25.0)
})

# ------------------------------------------------------------------ #
# R to Armadillo: Cubes                                              #
# ------------------------------------------------------------------ #

test_that("cube_col_means_: per-slice column means are correct", {
  slices <- list(
    matrix(1:6,   nrow = 2),   # slice 1 -> col means 2, 4, 6
    matrix(7:12,  nrow = 2),   # slice 2 -> col means 8, 10, 12
    matrix(13:18, nrow = 2)    # slice 3 -> col means 14, 16, 18
  )

  result <- cube_col_means_(slices)

  expected <- do.call(rbind, lapply(slices, colMeans))

  expect_true(is.matrix(result))
  expect_equal(dim(result), c(3L, 3L))   # 3 slices x 3 cols
  expect_equal(result, expected, ignore_attr = TRUE)
})

test_that("cube_col_means_: throws on mismatched matrix dimensions", {
  bad_slices <- list(
    matrix(1:6, nrow = 2),
    matrix(1:6, nrow = 3)   # different nrow
  )
  expect_error(cube_col_means_(bad_slices))
})

test_that("cube_col_means_: throws on empty list", {
  expect_error(cube_col_means_(list()))
})

# ------------------------------------------------------------------ #
# R to Armadillo: Fields                                             #
# ------------------------------------------------------------------ #

test_that("field_mat_demo_: L2-normalises each column of each matrix", {
  mats <- list(
    matrix(c(3.0, 4.0), nrow = 2),   # ||col|| = 5
    matrix(1:12 * 1.0, nrow = 4)
  )

  result <- field_mat_demo_(mats)

  expect_equal(length(result), 2L)

  # First matrix: single column [3,4], normalised -> [0.6, 0.8]
  expect_equal(result[[1]], matrix(c(0.6, 0.8), nrow = 2),
               tolerance = 1e-12, ignore_attr = TRUE)

  # Each column of every output matrix should have unit L2 norm
  for (m in result) {
    col_norms <- sqrt(colSums(m^2))
    expect_equal(col_norms, rep(1.0, ncol(m)), tolerance = 1e-12)
  }
})

test_that("field_mat_demo_: handles ragged matrices (different nrow)", {
  mats <- list(
    matrix(1:6  * 1.0, nrow = 2),   # 2x3
    matrix(1:12 * 1.0, nrow = 4)    # 4x3 (different nrow)
  )
  result <- field_mat_demo_(mats)

  expect_equal(dim(result[[1]]), c(2L, 3L))
  expect_equal(dim(result[[2]]), c(4L, 3L))
})

test_that("field_imat_demo_: integer field roundtrip is lossless", {
  mats <- list(
    matrix(1L:6L,  nrow = 2),
    matrix(7L:18L, nrow = 3)
  )

  result <- field_imat_demo_(mats)

  expect_equal(length(result), 2L)
  expect_equal(result[[1]], mats[[1]])
  expect_equal(result[[2]], mats[[2]])
})

test_that("field_imat_demo_: handles single-element field", {
  mats <- list(matrix(1L:4L, nrow = 2))
  result <- field_imat_demo_(mats)
  expect_equal(result[[1]], mats[[1]])
})

test_that("field_vec_demo_: doubles each element of each vector", {
  vecs <- list(c(1.0, 2.0, 3.0), c(4.0, 5.0))

  result <- field_vec_demo_(vecs)

  expect_equal(length(result), 2L)
  expect_equal(result[[1]], vecs[[1]] * 2)
  expect_equal(result[[2]], vecs[[2]] * 2)
})

test_that("field_vec_demo_: handles ragged vectors (different lengths)", {
  vecs <- list(c(1.0), c(2.0, 3.0), c(4.0, 5.0, 6.0))

  result <- field_vec_demo_(vecs)

  expect_equal(lengths(result), c(1L, 2L, 3L))
})

test_that("field_str_demo_: appends '!' to every string", {
  words <- c("hello", "world", "armadillo")

  result <- field_str_demo_(words)

  expect_equal(result, paste0(words, "!"))
})

test_that("field_str_demo_: works on a single string", {
  expect_equal(field_str_demo_("test"), "test!")
})

# ------------------------------------------------------------------ #
# Armadillo to R: Matrices                                           #
# ------------------------------------------------------------------ #

test_that("mat_out_demo_: computes A'A correctly", {
  x <- matrix(1:9 * 1.0, nrow = 3)

  result   <- mat_out_demo_(x)
  expected <- t(x) %*% x

  expect_true(is.matrix(result))
  expect_equal(dim(result), c(3L, 3L))
  expect_equal(result, expected)
})

# ------------------------------------------------------------------ #
# Armadillo to R: Vectors                                            #
# ------------------------------------------------------------------ #

test_that("vec_out_demo_: L2-normalises a vector", {
  y <- c(3.0, 4.0)

  result   <- vec_out_demo_(y)
  expected <- c(0.6, 0.8)

  expect_true(is.numeric(result))
  expect_equal(result, expected, tolerance = 1e-12)
})

test_that("vec_out_demo_: result has unit L2 norm", {
  set.seed(1)
  y      <- rnorm(10)
  result <- vec_out_demo_(y)
  expect_equal(sqrt(sum(result^2)), 1.0, tolerance = 1e-12)
})

# ------------------------------------------------------------------ #
# Armadillo to R: Cubes                                              #
# ------------------------------------------------------------------ #

test_that("random_cube_: returns a list of matrices with correct dims", {
  set.seed(42)
  result <- random_cube_(3L, 4L, 2L)

  expect_true(is.list(result))
  expect_equal(length(result), 2L)
  expect_equal(dim(result[[1]]), c(3L, 4L))
  expect_equal(dim(result[[2]]), c(3L, 4L))
})

test_that("random_cube_: all elements are numeric matrices", {
  set.seed(1)
  result <- random_cube_(2L, 2L, 5L)
  for (m in result) {
    expect_true(is.matrix(m))
    expect_true(is.numeric(m))
  }
})

test_that("integer_cube_roundtrip_: integer slices are preserved", {
  slices <- list(
    matrix(1L:4L,  nrow = 2),
    matrix(5L:8L,  nrow = 2),
    matrix(9L:12L, nrow = 2)
  )

  result <- integer_cube_roundtrip_(slices)

  expect_equal(length(result), 3L)
  for (i in seq_along(slices)) {
    expect_equal(result[[i]], slices[[i]])
  }
})

# ------------------------------------------------------------------ #
# Armadillo to R: Fields (build_field_)                              #
# ------------------------------------------------------------------ #

test_that("build_field_: returns list with correct lengths", {
  set.seed(42)
  sizes  <- c(3L, 5L, 2L)
  result <- build_field_(sizes)

  expect_true(is.list(result))
  expect_equal(length(result), 3L)
  expect_equal(lengths(result), sizes)
})

test_that("build_field_: each element is a numeric vector", {
  set.seed(1)
  result <- build_field_(c(4L, 6L))
  for (v in result) {
    expect_true(is.numeric(v))
    expect_false(is.matrix(v))
  }
})

# ------------------------------------------------------------------ #
# Armadillo to R: as_sexp                                            #
# ------------------------------------------------------------------ #

test_that("as_sexp_demo_: sorts a vector in ascending order", {
  result <- as_sexp_demo_(c(3.0, 1.0, 2.0))

  expect_true(is.numeric(result))
  expect_equal(result, c(1.0, 2.0, 3.0))
})

test_that("as_sexp_demo_: already-sorted input is unchanged", {
  y <- c(1.0, 2.0, 3.0, 4.0, 5.0)
  expect_equal(as_sexp_demo_(y), y)
})
