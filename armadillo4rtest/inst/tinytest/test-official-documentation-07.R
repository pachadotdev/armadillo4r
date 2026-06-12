local({
  res121 <- find_nan1_(2)
  expect_true(is.integer(res121))

  res122 <- find_unique1_(2)
  expect_true(is.integer(res122))

  res123 <- flip1_(2)
  expect_true(is.list(res123))
  expect_true(is.double(res123[[1]]))

  res124 <- imag1_(2)
  expect_true(is.list(res124))
  expect_true(is.double(res124[[1]]))

  res125 <- ind2sub1_(2)
  expect_true(is.list(res125))

  res126 <- index_min1_(2)
  expect_true(is.double(res126))
  expect_equal(length(res126), 2)

  res127 <- inplace_trans1_(2)
  expect_true(is.double(res127))
  expect_equal(dim(res127), c(2, 2))

  res128 <- inplace_strans1_(2)
  expect_true(is.complex(res128))
  expect_equal(length(res128), 4)

  res129 <- intersect1_(5)
  expect_true(is.integer(res129))
  expect_equal(res129, 2:5)

  res130 <- join_rows1_(2)
  expect_true(is.list(res130))
  expect_equal(length(res130), 5)

  res131 <- join_cubes1_(2)
  expect_true(is.list(res131))
  expect_equal(length(res131), 7)

  res132 <- kron1_(2)
  expect_true(is.double(res132))
  expect_equal(dim(res132), c(6, 6))

  res133 <- log_det1_(2)
  expect_true(is.list(res133))
  expect_equal(length(res133), 2)

  res134 <- log_det_sympd1_(2)
  expect_true(is.list(res134))
  expect_equal(length(res134), 2)

  res135 <- logmat1_(2)
  expect_true(is.complex(res135))
  expect_equal(length(res135), 4)

  res136 <- logmat_sympd1_(2)
  expect_true(is.list(res136))
  expect_equal(length(res136), 2)

  res137 <- max1_(2)
  expect_true(is.list(res137))
  expect_equal(length(res137), 4)

  res138 <- nonzeros1_(2)
  expect_true(is.double(res138))

  res139 <- norm1_(2)
  expect_true(is.double(res139))
  expect_equal(length(res139), 5)

  res140 <- norm2est1_(2)
  expect_true(is.double(res140))
  expect_equal(length(res140), 1)
})
