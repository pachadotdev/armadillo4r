test_that("official documentation - 4", {
  res61 <- transpose2_(2L)
  expect_type(res61, "double")
  expect_equal(dim(res61), c(3, 2))

  A <- matrix(c(1, 0, 0, 1, 1, 0, 0, 1, 1), nrow = 3, ncol = 3, byrow = TRUE)
  b <- c(6.50, 7.50, 8.50)
  res62 <- inverse1_(A, b)
  expect_type(res62, "double")
  expect_equal(res62, solve(A, b))

  res63 <- maxmin1_(2)
  expect_type(res63, "double")
  expect_equal(length(res63), 2)

  res64 <- index_maxmin1_(2)
  expect_type(res64, "double")
  expect_equal(length(res64), 6)

  res65 <- in_range1_(2)
  expect_type(res65, "logical")
  expect_equal(length(res65), 3)

  res66 <- is_empty1_(2)
  expect_type(res66, "logical")
  expect_equal(length(res66), 2)

  res67 <- is_vec1_(2)
  expect_type(res67, "logical")
  expect_equal(length(res67), 5)

  res68 <- is_sorted1_(2)
  expect_type(res68, "logical")
  expect_equal(length(res68), 4)

  res69 <- is_triangular1_(2)
  expect_type(res69, "logical")
  expect_equal(length(res69), 3)

  res70 <- is_diagonal1_(2)
  expect_type(res70, "logical")
  expect_equal(length(res70), 3)

  res71 <- is_square1_(2)
  expect_type(res71, "logical")
  expect_equal(length(res71), 3)

  res72 <- is_symmetric1_(2)
  expect_type(res72, "logical")
  expect_equal(length(res72), 3)

  res73 <- is_hermitian1_(2)
  expect_type(res73, "logical")
  expect_equal(length(res73), 3)

  res74 <- is_sympd1_(2)
  expect_type(res74, "logical")
  expect_equal(length(res74), 3)

  res75 <- is_zero1_(2)
  expect_type(res75, "logical")
  expect_equal(length(res75), 3)

  res76 <- is_finite1_(2)
  expect_type(res76, "logical")
  expect_equal(length(res76), 3)

  res77 <- has_inf1_(2)
  expect_type(res77, "logical")
  expect_equal(length(res77), 3)

  res78 <- has_nan1_(2)
  expect_type(res78, "logical")
  expect_equal(length(res78), 3)

  res79 <- linspace1_(10)
  expect_type(res79, "double")
  expect_equal(length(res79), 10)

  res80 <- logspace1_(10)
  expect_type(res80, "double")
  expect_equal(length(res80), 10)
})
