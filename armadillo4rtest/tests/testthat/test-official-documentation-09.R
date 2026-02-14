test_that("official documentation - 9", {
  res161 <- sub2ind1_(2)
  expect_type(res161, "integer")
  expect_equal(length(res161), 1)

  res162 <- trace1_(2)
  expect_type(res162, "double")
  expect_equal(length(res162), 1)

  res163 <- trans1_(2)
  expect_type(res163, "list")
  expect_equal(length(res163), 2)

  res164 <- trapz1_(2)
  expect_type(res164, "double")
  expect_equal(length(res164), 1)

  set.seed(123)
  X <- matrix(rnorm(4), nrow = 2, ncol = 2)
  Y <- matrix(rnorm(4), nrow = 2, ncol = 2)

  res165 <- mean1_(X, Y)
  res166 <- median1_(X, Y)
  res167 <- stddev1_(X, Y)
  res168 <- var1_(X, Y)
  res169 <- range1_(X, Y)
  res170 <- cov1_(X, Y)
  res171 <- cor1_(X, Y)

  expect_type(res165, "list")
  expect_equal(length(res165), 3)

  expect_type(res166, "list")
  expect_equal(length(res166), 3)
  expect_equal(res165, res166)

  expect_type(res167, "list")
  expect_equal(length(res167), 3)

  expect_type(res168, "list")
  expect_equal(length(res168), 3)

  expect_type(res169, "list")
  expect_equal(length(res169), 2)

  expect_type(res170, "list")
  expect_equal(length(res170), 2)

  expect_type(res171, "list")
  expect_equal(length(res171), 2)

  res172 <- normpdf1_(5)
  expect_type(res172, "list")
  expect_equal(length(res172), 5)

  res173 <- lognormpdf1_(5)
  expect_type(res173, "list")
  expect_equal(length(res173), 5)

  res174 <- normcdf1_(5)
  expect_type(res174, "list")
  expect_equal(length(res174), 5)

  res175 <- mvnrnd1_(3, 5)
  expect_type(res175, "double")
  expect_equal(dim(res175), c(3, 5))

  res176 <- chi2rnd1_(3, 5)
  expect_type(res176, "list")
  expect_equal(length(res176), 2)
  expect_equal(dim(res176[[1]]), c(3, 5))

  res177 <- wishrnd1_(3)
  expect_type(res177, "double")
  expect_equal(dim(res177), c(3, 3))

  res178 <- iwishrnd1_(3, 4)
  expect_type(res178, "double")
  expect_equal(dim(res178), c(3, 3))

  res179 <- kmeans1_(4, 3)
  expect_type(res179, "list")
  # expect_equal(res179[[1]], TRUE)
  # expect_type(res179[[2]], "double")
  # expect_equal(dim(res179[[2]]), c(3, 2))
  # TODO: add RNG later

  set.seed(321)
  x <- rnorm(10, 0, 1)
  y <- rnorm(10, 2, 3)
  res180 <- conv1_(x, y)
  expect_type(res180, "list")
  expect_equal(length(res180[[1]]), length(x) + length(y) - 1)
  expect_equal(length(res180[[2]]), length(x))
})
