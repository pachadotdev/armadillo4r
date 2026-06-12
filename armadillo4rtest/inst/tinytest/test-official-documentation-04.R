source(system.file("tinytest", "helper-sparse.R", package = "armadillo4rtest"))

local({
  A <- matrix(c(1, 0, 0, 1, 1, 0, 0, 1, 1), nrow = 3, ncol = 3, byrow = TRUE)
  b <- c(6.50, 7.50, 8.50)
  res62 <- inverse1_(A, b)
  expect_true(is.double(res62))
  expect_equal(res62, solve(A, b))

  res63 <- maxmin1_(2)
  expect_true(is.double(res63))
  expect_equal(length(res63), 2)

  res64 <- index_maxmin1_(2)
  expect_true(is.double(res64))
  expect_equal(length(res64), 6)

  res65 <- in_range1_(2)
  expect_true(is.logical(res65))
  expect_equal(length(res65), 3)

  res66 <- is_empty1_(2)
  expect_true(is.logical(res66))
  expect_equal(length(res66), 2)

  res67 <- is_vec1_(2)
  expect_true(is.logical(res67))
  expect_equal(length(res67), 5)

  res68 <- is_sorted1_(2)
  expect_true(is.logical(res68))
  expect_equal(length(res68), 4)

  res69 <- is_triangular1_(2)
  expect_true(is.logical(res69))
  expect_equal(length(res69), 3)

  res70 <- is_diagonal1_(2)
  expect_true(is.logical(res70))
  expect_equal(length(res70), 3)

  res71 <- is_square1_(2)
  expect_true(is.logical(res71))
  expect_equal(length(res71), 3)

  res72 <- is_symmetric1_(2)
  expect_true(is.logical(res72))
  expect_equal(length(res72), 3)

  res73 <- is_hermitian1_(2)
  expect_true(is.logical(res73))
  expect_equal(length(res73), 3)

  res74 <- is_sympd1_(2)
  expect_true(is.logical(res74))
  expect_equal(length(res74), 3)

  res79 <- linspace1_(10)
  expect_true(is.double(res79))
  expect_equal(length(res79), 10)

  res80 <- logspace1_(10)
  expect_true(is.double(res80))
  expect_equal(length(res80), 10)
})

# official documentation - 4 (sparse)
local({
  if (!skip_if_no_sparse()) return(invisible(NULL))

  res61 <- transpose2_(2L)
  expect_true(is.double(res61))
  expect_equal(dim(res61), c(3, 2))
  
  res75 <- is_zero1_(2)
  expect_true(is.logical(res75))
  expect_equal(length(res75), 3)

  res76 <- is_finite1_(2)
  expect_true(is.logical(res76))
  expect_equal(length(res76), 3)

  res77 <- has_inf1_(2)
  expect_true(is.logical(res77))
  expect_equal(length(res77), 3)

  res78 <- has_nan1_(2)
  expect_true(is.logical(res78))
  expect_equal(length(res78), 3)
})
