source(system.file("tinytest", "helper-sparse.R", package = "armadillo4rtest"))

local({
  res81 <- regspace1_(0.1)
  expect_true(is.double(res81))
  expect_equal(length(res81), 11)

  res82 <- randperm1_(5, 3)
  expect_true(is.integer(res82))
  expect_equal(length(res82), 5 + 3)

  res83 <- eye2_(2)
  expect_true(is.double(res83))
  expect_equal(dim(res83), c(2, 2))

  res84 <- ones2_(2)
  expect_true(is.double(res84))
  expect_equal(dim(res84), c(2, 2))

  res85 <- zeros2_(2)
  expect_true(is.double(res85))
  expect_equal(dim(res85), c(2, 2))

  res86 <- randu3_(2)
  expect_true(is.double(res86))
  expect_equal(dim(res86), c(2, 2))

  res87 <- randn3_(2)
  expect_true(is.double(res87))
  expect_equal(dim(res87), c(2, 2))

  res88 <- randg3_(2)
  expect_true(is.double(res88))
  expect_equal(dim(res88), c(2, 2))

  res92 <- toeplitz1_(2)
  expect_true(is.double(res92))
  expect_equal(dim(res92), c(2, 2))

  res93 <- abs1_(2)
  expect_true(is.double(res93))
  expect_equal(dim(res93), c(2, 2))

  res94 <- accu1_(2)
  expect_true(is.double(res94))
  expect_equal(length(res94), 1)

  res95 <- affmul1_(2)
  expect_true(is.double(res95))
  expect_equal(length(res95), 2)

  res96 <- all1_(2)
  expect_true(is.logical(res96))
  expect_equal(length(res96), 4)

  res97 <- any1_(2)
  expect_true(is.logical(res97))
  expect_equal(length(res97), 4)

  res98 <- approx_equal1_(2)
  expect_true(is.logical(res98))
  expect_equal(length(res98), 1)

  res99 <- arg1_(2)
  expect_true(is.double(res99))
  expect_equal(dim(res99), c(2, 2))

  res100 <- as_scalar1_(2)
  expect_true(is.double(res100))
  expect_equal(length(res100), 1)
})

# official documentation - 5 (sparse)
local({
  if (!skip_if_no_sparse()) return(invisible(NULL))

  res89 <- speye1_(2)
  expect_true(is.double(res89))
  expect_equal(dim(res89), c(2, 2))

  res90 <- spones1_(2)
  expect_true(is.double(res90))
  expect_equal(dim(res90), c(2, 2))

  res91 <- sprandu1_(2)
  expect_true(is.double(res91))
  expect_equal(dim(res91), c(2, 2))

  res92 <- sprandn1_(2)
  expect_true(is.double(res92))
  expect_equal(dim(res92), c(2, 2))
})
