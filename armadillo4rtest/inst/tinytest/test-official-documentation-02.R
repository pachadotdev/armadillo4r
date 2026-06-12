local({
  res21 <- replace1_(2L)
  expect_true(is.double(res21))
  expect_equal(diag(res21), rep(0, 2))

  res22 <- clamp1_(2L)
  expect_true(is.double(res22))
  expect_equal(diag(res22), rep(0.2, 2))

  res23 <- transform1_(2L)
  expect_true(is.double(res23))
  expect_equal(diag(res23), rep(123, 2))

  res24 <- for_each1_(2L)
  expect_true(is.double(res24))
  expect_equal(dim(res24), c(2, 2))

  res25 <- set_size1_(2L)
  expect_true(is.double(res25))
  expect_equal(length(res25), 2)

  res26 <- reshape1_(2L)
  expect_true(is.double(res26))
  expect_equal(dim(res26), c(2 - 1, 2 + 1))

  res27 <- resize1_(2L)
  expect_true(is.double(res27))
  expect_equal(dim(res27), c(2 - 1, 2 + 1))

  res28 <- copy_size1_(2L)
  expect_true(is.integer(res28))
  expect_equal(length(res28), 2)

  res29 <- reset1_(2L)
  expect_true(is.integer(res29))
  expect_equal(length(res29), 2)

  res30 <- subview1_(5L)
  expect_true(is.double(res30))
  expect_equal(dim(res30), c(5, 5))

  res31 <- subview2_(5L)
  expect_true(is.double(res31))
  expect_equal(dim(res31), c(5, 3))

  res32 <- diagonal1_(2L)
  expect_true(is.double(res32))
  expect_equal(length(res32), 2)

  res33 <- each_col1_(2L)
  expect_true(is.double(res33))
  expect_equal(dim(res33), c(2, 3))

  res34 <- each_row1_(2L)
  expect_true(is.double(res34))
  expect_equal(dim(res34), c(3, 2))

  res35 <- each_slice1_(2L)
  expect_true(is.double(res35))
  expect_equal(dim(res35), c(2, 3))

  res36 <- set_real1_(2L)
  expect_true(is.complex(res36))
  expect_equal(dim(res36), c(3, 1))

  res37 <- set_real2_(2L)
  expect_true(is.complex(res37))
  expect_equal(dim(res37), c(1, 3))

  res38 <- set_imag1_(2L)
  expect_true(is.complex(res38))
  expect_equal(dim(res38), c(3, 1))

  res39 <- insert_columns1_(2L)
  expect_true(is.double(res39))
  expect_equal(dim(res39), c(2, 5))

  res40 <- insert_rows1_(2L)
  expect_true(is.double(res40))
  expect_equal(dim(res40), c(5, 2))
})
