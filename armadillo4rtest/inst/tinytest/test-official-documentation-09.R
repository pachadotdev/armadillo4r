local({
  res161 <- sub2ind1_(2)
  expect_true(is.integer(res161))
  expect_equal(length(res161), 1)

  res162 <- trace1_(2)
  expect_true(is.double(res162))
  expect_equal(length(res162), 1)

  res163 <- trans1_(2)
  expect_true(is.list(res163))
  expect_equal(length(res163), 2)

  res164 <- trapz1_(2)
  expect_true(is.double(res164))
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

  expect_true(is.list(res165))
  expect_equal(length(res165), 3)

  expect_true(is.list(res166))
  expect_equal(length(res166), 3)
  expect_equal(res165, res166)

  expect_true(is.list(res167))
  expect_equal(length(res167), 3)

  expect_true(is.list(res168))
  expect_equal(length(res168), 3)

  expect_true(is.list(res169))
  expect_equal(length(res169), 2)

  expect_true(is.list(res170))
  expect_equal(length(res170), 2)

  expect_true(is.list(res171))
  expect_equal(length(res171), 2)

  res172 <- normpdf1_(5)
  expect_true(is.list(res172))
  expect_equal(length(res172), 5)

  res173 <- lognormpdf1_(5)
  expect_true(is.list(res173))
  expect_equal(length(res173), 5)

  res174 <- normcdf1_(5)
  expect_true(is.list(res174))
  expect_equal(length(res174), 5)

  res175 <- mvnrnd1_(3, 5)
  expect_true(is.double(res175))
  expect_equal(dim(res175), c(3, 5))

  res176 <- chi2rnd1_(3, 5)
  expect_true(is.list(res176))
  expect_equal(length(res176), 2)
  expect_equal(dim(res176[[1]]), c(3, 5))

  res177 <- wishrnd1_(3)
  expect_true(is.double(res177))
  expect_equal(dim(res177), c(3, 3))

  res178 <- iwishrnd1_(3, 4)
  expect_true(is.double(res178))
  expect_equal(dim(res178), c(3, 3))

  res179 <- kmeans1_(4, 3)
  expect_true(is.list(res179))
  
  set.seed(321)
  x <- rnorm(10, 0, 1)
  y <- rnorm(10, 2, 3)
  res180 <- conv1_(x, y)
  expect_true(is.list(res180))
  expect_equal(length(res180[[1]]), length(x) + length(y) - 1)
  expect_equal(length(res180[[2]]), length(x))
})
