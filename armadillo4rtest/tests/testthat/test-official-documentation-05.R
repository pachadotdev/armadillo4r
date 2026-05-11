test_that("official documentation - 5", {
  res81 <- regspace1_(0.1)
  expect_type(res81, "double")
  expect_equal(length(res81), 11)

  res82 <- randperm1_(5, 3)
  expect_type(res82, "integer")
  expect_equal(length(res82), 5 + 3)

  res83 <- eye2_(2)
  expect_type(res83, "double")
  expect_equal(dim(res83), c(2, 2))

  res84 <- ones2_(2)
  expect_type(res84, "double")
  expect_equal(dim(res84), c(2, 2))

  res85 <- zeros2_(2)
  expect_type(res85, "double")
  expect_equal(dim(res85), c(2, 2))

  res86 <- randu3_(2)
  expect_type(res86, "double")
  expect_equal(dim(res86), c(2, 2))

  res87 <- randn3_(2)
  expect_type(res87, "double")
  expect_equal(dim(res87), c(2, 2))

  res88 <- randg3_(2)
  expect_type(res88, "double")
  expect_equal(dim(res88), c(2, 2))

  res92 <- toeplitz1_(2)
  expect_type(res92, "double")
  expect_equal(dim(res92), c(2, 2))

  res93 <- abs1_(2)
  expect_type(res93, "double")
  expect_equal(dim(res93), c(2, 2))

  res94 <- accu1_(2)
  expect_type(res94, "double")
  expect_equal(length(res94), 1)

  res95 <- affmul1_(2)
  expect_type(res95, "double")
  expect_equal(length(res95), 2)

  res96 <- all1_(2)
  expect_type(res96, "logical")
  expect_equal(length(res96), 4)

  res97 <- any1_(2)
  expect_type(res97, "logical")
  expect_equal(length(res97), 4)

  res98 <- approx_equal1_(2)
  expect_type(res98, "logical")
  expect_equal(length(res98), 1)

  res99 <- arg1_(2)
  expect_type(res99, "double")
  expect_equal(dim(res99), c(2, 2))

  res100 <- as_scalar1_(2)
  expect_type(res100, "double")
  expect_equal(length(res100), 1)
})

test_that("official documentation - 5 (sparse)", {
  skip_if_no_sparse()

  res89 <- speye1_(2)
  expect_type(res89, "double")
  expect_equal(dim(res89), c(2, 2))

  res90 <- spones1_(2)
  expect_type(res90, "double")
  expect_equal(dim(res90), c(2, 2))

  res91 <- sprandu1_(2)
  expect_type(res91, "double")
  expect_equal(dim(res91), c(2, 2))

  res92 <- sprandn1_(2)
  expect_type(res92, "double")
  expect_equal(dim(res92), c(2, 2))
})
