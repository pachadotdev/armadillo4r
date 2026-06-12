local({
  res141 <- normalise1_(2)
  expect_true(is.list(res141))
  expect_equal(length(res141), 2)

  res142 <- pow1_(2)
  expect_true(is.list(res142))
  expect_equal(length(res142), 2)

  res143 <- powmat1_(2)
  expect_true(is.list(res143))
  expect_equal(length(res143), 2)

  res144 <- prod1_(2)
  expect_true(is.list(res144))
  expect_equal(length(res144), 2)

  res145 <- rank1_(2)
  expect_true(is.list(res145))
  expect_equal(length(res145), 2)

  res146 <- rcond1_(2)
  expect_true(is.double(res146))
  expect_equal(length(res146), 1)

  res147 <- repelem1_(2)
  expect_true(is.list(res147))
  expect_equal(length(res147), 2)

  res148 <- repmat1_(2)
  expect_true(is.list(res148))
  expect_equal(length(res148), 2)

  res149 <- reshape2_(2)
  expect_true(is.list(res149))
  expect_equal(length(res149), 3)

  res150 <- resize2_(2)
  expect_true(is.list(res150))
  expect_equal(length(res150), 3)

  res151 <- reverse1_(2)
  expect_true(is.list(res151))
  expect_equal(length(res151), 3)

  res152 <- roots1_(2)
  expect_true(is.complex(res152))
  expect_equal(length(res152), 1)

  res153 <- shift1_(2)
  expect_true(is.list(res153))
  expect_equal(length(res153), 3)

  res154 <- shuffle1_(2)
  expect_true(is.list(res154))
  expect_equal(length(res154), 2)

  res155 <- size1_(2)
  expect_true(is.list(res155))
  expect_equal(length(res155), 7)

  res156 <- sort1_(2)
  expect_true(is.list(res156))
  expect_equal(length(res156), 5)

  res157 <- sort_index1_(2)
  expect_true(is.list(res157))
  expect_equal(length(res157), 3)

  res158 <- sqrtmat1_(2)
  expect_true(is.list(res158))
  expect_equal(length(res158), 4)

  res159 <- sqrtmat_sympd1_(2)
  expect_true(is.double(res159))
  expect_equal(dim(res159), c(2, 2))

  res160 <- sum2_(2)
  expect_true(is.list(res160))
  expect_equal(length(res160), 3)
})
