test_that("official documentation - 1", {
  set.seed(123)
  a <- matrix(runif(4), nrow = 2, ncol = 2)
  b <- matrix(runif(4), nrow = 2, ncol = 2)

  res1 <- matrix1_(a)
  expect_type(res1, "double")
  expect_equal(dim(res1), c(2, 2))

  res2 <- matrix2_(a)
  expect_type(res2, "list")
  expect_type(res2[[1]], "double")
  expect_type(res2[[2]], "double")
  expect_equal(dim(res2[[1]]), c(2, 2))
  expect_equal(dim(res2[[2]]), c(2, 2))

  set.seed(123)
  x <- runif(10)
  y <- rep(1, 10)

  res3 <- column1_(x, y)
  expect_type(res3, "double")
  expect_equal(length(res3), 10)

  res4 <- row1_(x, y)
  expect_type(res4, "double")

  res2 <- cube1_(a, b)
  expect_type(res2, "double")
  expect_equal(res2, (2 * a) + (b * b))

  res6 <- field1_(a, b)
  expect_type(res6, "double")
  expect_equal(res6, a + b + t(a) + t(b))

  res7 <- attr1_(a)
  expect_type(res7, "integer")
  expect_equal(res7, c("n_rows" = 2, "n_cols" = 2, "n_elem" = 4))

  res8 <- access1_(a)
  expect_type(res8, "double")
  expect_equal(dim(res8), c(2, 2))

  res9 <- initialization1_(a)
  expect_type(res9, "double")
  expect_equal(dim(res9), c(2, 2))

  res10 <- zeros1_(a)
  expect_type(res10, "double")
  expect_equal(res10, matrix(0, nrow = 2, ncol = 2))

  res11 <- ones1_(a)
  expect_type(res11, "double")
  expect_equal(res11, matrix(3, nrow = 2, ncol = 2))

  res12 <- eye1_(a)
  expect_type(res12, "double")
  expect_equal(res12, 3 * diag(2))

  res13 <- randu1_(a)
  expect_type(res13, "double")
  expect_equal(dim(res13), c(2, 2))

  res14 <- randn1_(a)
  expect_type(res14, "double")
  expect_equal(dim(res14), c(2, 2))

  set.seed(123)
  res15 <- randu2_(2L)

  set.seed(123)
  res15_2 <- randu2_(2L)

  set.seed(321)
  res15_3 <- randu2_(2L)

  expect_equal(res15, res15_2)
  res15_4 <- all.equal(res15, res15_3)
  expect_match(res15_4, "Mean relative difference")

  set.seed(123)
  res16 <- randn2_(2L)

  set.seed(123)
  res16_2 <- randn2_(2L)

  set.seed(321)
  res16_3 <- randn2_(2L)

  expect_equal(res16, res16_2)
  res16_4 <- all.equal(res16, res16_3)
  expect_match(res16_4, "Mean relative difference")

  res17 <- fill1_(a)
  expect_type(res17, "double")
  expect_equal(dim(res17), c(2, 2))

  res18 <- imbue1_(a)
  expect_type(res18, "double")
  expect_equal(dim(res18), c(2, 2))

  set.seed(123)
  res19 <- imbue2_(a)

  set.seed(123)
  res19_2 <- imbue2_(a)

  set.seed(321)
  res19_3 <- imbue2_(a)

  expect_type(res19, "double")
  expect_equal(res19, res19_2)
  res19_4 <- all.equal(res19, res19_3)
  expect_match(res19_4, "Mean relative difference")

  res20 <- clean1_(2L)
  expect_type(res20, "double")
  expect_equal(diag(res20), rep(0, 2))
})
