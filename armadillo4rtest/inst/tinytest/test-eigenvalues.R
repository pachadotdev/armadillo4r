# armadillo4r vs base R (sorted)
local({
  x <- mtcars_mat$x
  y <- mtcars_mat$y

  x <- x[, c("wt", "cyl4", "cyl6", "cyl8")]

  x <- cor(x)

  # Armadillo computation
  a <- sort(eigen_sym_mat(x))

  # Base R computation
  b <- sort(eigen(x)$values)

  expect_equal(a, b)
})

# eigen_gen wrapper works as expected
local({
  x <- mtcars_mat$x
  y <- mtcars_mat$y

  x <- x[, c("wt", "cyl4", "cyl6", "cyl8")]

  x <- cor(x)

  expect_equal(eigen_gen_mat(x)$real, Re(eigen_gen_mat_complex_wrapper(x)))

  expect_equal(Re(eigen_gen_mat_complex_wrapper(x)), eigen_gen_no_wrapper(x)$real)

  # case where the imaginary part is not zero

  x <- matrix(c(4 / 5, 3 / 5, 1, -3 / 5, 4 / 5, 2, 0, 0, 2), 3, 3)

  a <- eigen_gen_mat_complex_wrapper(x)

  b <- sort(a)

  c <- sort(eigen(x)$values)

  expect_equal(b, c)
})
