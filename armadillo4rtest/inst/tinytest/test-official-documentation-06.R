source(system.file("tinytest", "helper-sparse.R", package = "armadillo4rtest"))

local({
  res101 <- clamp2_(2)
  expect_true(is.double(res101))
  expect_equal(dim(res101), c(2, 2))

  res102 <- cond1_(2)
  expect_true(is.double(res102))
  expect_equal(length(res102), 1)

  res103 <- conj1_(2)
  expect_true(is.complex(res103))
  expect_equal(dim(res103), c(2, 2))

  res104 <- conv_to1_(2)
  expect_true(is.double(res104))
  expect_equal(length(res104), 4)

  res105 <- cross1_(3)
  expect_true(is.double(res105))
  expect_equal(length(res105), 3)

  res106 <- cumsum1_(2)
  expect_true(is.double(res106))
  expect_equal(length(res106), 3)

  res107 <- cumprod1_(2)
  expect_true(is.double(res107))
  expect_equal(length(res107), 3)

  res108 <- det1_(2)
  expect_true(is.double(res108))
  expect_equal(length(res108), 3)

  res109 <- diagmat1_(2)
  expect_true(is.double(res109))
  expect_equal(dim(res109), c(2, 2))

  res110 <- diagvec1_(3)
  expect_true(is.double(res110))
  expect_equal(length(res110), 2)

  res111 <- diags1_(2)
  expect_true(is.double(res111))
  expect_equal(dim(res111), c(2, 2))

  res113 <- diff1_(3)
  expect_true(is.double(res113))
  expect_equal(dim(res113), c(3, 2))

  res114 <- dot1_(2)
  expect_true(is.double(res114))
  expect_equal(length(res114), 3)

  res115 <- eps1_(2)
  expect_true(is.double(res115))
  expect_equal(dim(res115), c(2, 2))

  res116 <- expmat1_(2)
  expect_true(is.double(res116))
  expect_equal(dim(res116), c(2, 2))

  res117 <- expmat_sym1_(2)
  expect_true(is.double(res117))
  expect_equal(dim(res117), c(2, 2))

  res118 <- find1_(2)
  expect_true(is.list(res118))

  res119 <- find_finite1_(2)
  expect_true(is.integer(res119))
  expect_equal(length(res119), 4)

  res120 <- find_nonfinite1_(2)
  expect_true(is.integer(res120))
})

# official documentation - 6 (sparse)
local({
  if (!skip_if_no_sparse()) return(invisible(NULL))
  res112 <- spdiags1_(2)
  expect_true(is.double(res112))
  expect_equal(dim(res112), c(2, 2))
})
