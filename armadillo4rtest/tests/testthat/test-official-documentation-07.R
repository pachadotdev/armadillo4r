test_that("official documentation - 7", {
  res121 <- find_nan1_(2)
  expect_type(res121, "integer")

  res122 <- find_unique1_(2)
  expect_type(res122, "integer")

  res123 <- flip1_(2)
  expect_type(res123, "list")
  expect_type(res123[[1]], "double")

  res124 <- imag1_(2)
  expect_type(res124, "list")
  expect_type(res124[[1]], "double")

  res125 <- ind2sub1_(2)
  expect_type(res125, "list")

  res126 <- index_min1_(2)
  expect_type(res126, "double")
  expect_equal(length(res126), 2)

  res127 <- inplace_trans1_(2)
  expect_type(res127, "double")
  expect_equal(dim(res127), c(2, 2))

  res128 <- inplace_strans1_(2)
  expect_type(res128, "complex")
  expect_equal(length(res128), 4)

  res129 <- intersect1_(5)
  expect_type(res129, "integer")
  expect_equal(res129, 2:5)

  res130 <- join_rows1_(2)
  expect_type(res130, "list")
  expect_equal(length(res130), 5)

  res131 <- join_cubes1_(2)
  expect_type(res131, "list")
  expect_equal(length(res131), 7)

  res132 <- kron1_(2)
  expect_type(res132, "double")
  expect_equal(dim(res132), c(6, 6))

  res133 <- log_det1_(2)
  expect_type(res133, "list")
  expect_equal(length(res133), 2)

  res134 <- log_det_sympd1_(2)
  expect_type(res134, "list")
  expect_equal(length(res134), 2)

  res135 <- logmat1_(2)
  expect_type(res135, "complex")
  expect_equal(length(res135), 4)

  res136 <- logmat_sympd1_(2)
  expect_type(res136, "list")
  expect_equal(length(res136), 2)

  res137 <- max1_(2)
  expect_type(res137, "list")
  expect_equal(length(res137), 4)

  res138 <- nonzeros1_(2)
  expect_type(res138, "double")

  res139 <- norm1_(2)
  expect_type(res139, "double")
  expect_equal(length(res139), 5)

  res140 <- norm2est1_(2)
  expect_type(res140, "double")
  expect_equal(length(res140), 1)
})
