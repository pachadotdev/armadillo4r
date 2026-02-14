test_that("official documentation - 6", {
  res101 <- clamp2_(2)
  expect_type(res101, "double")
  expect_equal(dim(res101), c(2, 2))

  res102 <- cond1_(2)
  expect_type(res102, "double")
  expect_equal(length(res102), 1)

  res103 <- conj1_(2)
  expect_type(res103, "complex")
  expect_equal(dim(res103), c(2, 2))

  res104 <- conv_to1_(2)
  expect_type(res104, "double")
  expect_equal(length(res104), 4)

  res105 <- cross1_(3)
  expect_type(res105, "double")
  expect_equal(length(res105), 3)

  res106 <- cumsum1_(2)
  expect_type(res106, "double")
  expect_equal(length(res106), 3)

  res107 <- cumprod1_(2)
  expect_type(res107, "double")
  expect_equal(length(res107), 3)

  res108 <- det1_(2)
  expect_type(res108, "double")
  expect_equal(length(res108), 3)

  res109 <- diagmat1_(2)
  expect_type(res109, "double")
  expect_equal(dim(res109), c(2, 2))

  res110 <- diagvec1_(3)
  expect_type(res110, "double")
  expect_equal(length(res110), 2)

  res111 <- diags1_(2)
  expect_type(res111, "double")
  expect_equal(dim(res111), c(2, 2))

  res112 <- spdiags1_(2)
  expect_type(res112, "double")
  expect_equal(dim(res112), c(2, 2))

  res113 <- diff1_(3)
  expect_type(res113, "double")
  expect_equal(dim(res113), c(3, 2))

  res114 <- dot1_(2)
  expect_type(res114, "double")
  expect_equal(length(res114), 3)

  res115 <- eps1_(2)
  expect_type(res115, "double")
  expect_equal(dim(res115), c(2, 2))

  res116 <- expmat1_(2)
  expect_type(res116, "double")
  expect_equal(dim(res116), c(2, 2))

  res117 <- expmat_sym1_(2)
  expect_type(res117, "double")
  expect_equal(dim(res117), c(2, 2))

  res118 <- find1_(2)
  expect_type(res118, "list")

  res119 <- find_finite1_(2)
  expect_type(res119, "integer")
  expect_equal(length(res119), 4)

  res120 <- find_nonfinite1_(2)
  expect_type(res120, "integer")
})
