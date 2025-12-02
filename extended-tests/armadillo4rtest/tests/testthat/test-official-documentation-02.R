test_that("official documentation - 2", {
  res21 <- replace1_(2L)
  expect_type(res21, "double")
  expect_equal(diag(res21), rep(0, 2))

  res22 <- clamp1_(2L)
  expect_type(res22, "double")
  expect_equal(diag(res22), rep(0.2, 2))

  res23 <- transform1_(2L)
  expect_type(res23, "double")
  expect_equal(diag(res23), rep(123, 2))

  res24 <- for_each1_(2L)
  expect_type(res24, "double")
  expect_equal(dim(res24), c(2, 2))

  res25 <- set_size1_(2L)
  expect_type(res25, "double")
  expect_equal(length(res25), 2)

  res26 <- reshape1_(2L)
  expect_type(res26, "double")
  expect_equal(dim(res26), c(2 - 1, 2 + 1))

  res27 <- resize1_(2L)
  expect_type(res27, "double")
  expect_equal(dim(res27), c(2 - 1, 2 + 1))

  res28 <- copy_size1_(2L)
  expect_type(res28, "integer")
  expect_equal(length(res28), 2)

  res29 <- reset1_(2L)
  expect_type(res29, "integer")
  expect_equal(length(res29), 2)

  res30 <- subview1_(5L)
  expect_type(res30, "double")
  expect_equal(dim(res30), c(5, 5))

  res31 <- subview2_(5L)
  expect_type(res31, "double")
  expect_equal(dim(res31), c(5, 3))

  res32 <- diagonal1_(2L)
  expect_type(res32, "double")
  expect_equal(length(res32), 2)

  res33 <- each_col1_(2L)
  expect_type(res33, "double")
  expect_equal(dim(res33), c(2, 3))

  res34 <- each_row1_(2L)
  expect_type(res34, "double")
  expect_equal(dim(res34), c(3, 2))

  res35 <- each_slice1_(2L)
  expect_type(res35, "double")
  expect_equal(dim(res35), c(2, 3))

  res36 <- set_real1_(2L)
  expect_type(res36, "complex")
  expect_equal(dim(res36), c(3, 1))

  res37 <- set_real2_(2L)
  expect_type(res37, "complex")
  expect_equal(dim(res37), c(1, 3))

  res38 <- set_imag1_(2L)
  expect_type(res38, "complex")
  expect_equal(dim(res38), c(3, 1))

  res39 <- insert_columns1_(2L)
  expect_type(res39, "double")
  expect_equal(dim(res39), c(2, 5))

  res40 <- insert_rows1_(2L)
  expect_type(res40, "double")
  expect_equal(dim(res40), c(5, 2))
})
