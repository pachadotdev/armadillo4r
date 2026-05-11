test_that("official documentation - 3", {
  res41 <- insert_slices1_(2L)
  expect_type(res41, "double")
  expect_equal(dim(res41), c(2, 2))

  res42 <- shed_columns1_(2L)
  expect_type(res42, "double")
  expect_equal(dim(res42), c(2, 5))

  res42 <- shed_rows1_(2L)
  expect_type(res42, "double")
  expect_equal(dim(res42), c(5, 2))

  res43 <- shed_slices1_(2L)
  expect_type(res43, "double")
  expect_equal(dim(res43), c(2, 2))

  res44 <- swap_columns1_(2L)
  expect_type(res44, "double")
  expect_equal(dim(res44), c(2, 10))

  res45 <- swap_rows1_(2L)
  expect_type(res45, "double")
  expect_equal(dim(res45), c(10, 2))

  res46 <- swap1_(2L)
  expect_type(res46, "double")
  expect_equal(dim(res46), c(4, 1))

  res47 <- memptr1_(2L)
  expect_type(res47, "double")
  expect_equal(dim(res47), c(2, 2))

  res48 <- colptr1_(2L)
  expect_type(res48, "double")
  expect_equal(dim(res48), c(2, 2))

  res49 <- iterators1_(2L)
  expect_type(res49, "double")
  expect_equal(dim(res49), c(2, 3))

  res50 <- iterators2_(2L)
  expect_type(res50, "double")
  expect_equal(dim(res50), c(2, 3))

  res52 <- iterators4_(2L)
  expect_type(res52, "double")
  expect_equal(dim(res52), c(2, 2))

  res53 <- compatibility1_(2L)
  expect_type(res53, "double")
  expect_equal(length(res53), 2)

  res54 <- compatibility2_(2L)
  expect_type(res54, "integer")
  expect_equal(length(res54), 2)

  res55 <- as_col1_(2L)
  expect_type(res55, "double")
  expect_equal(length(res55), 6)

  res56 <- as_row1_(2L)
  expect_type(res56, "double")
  expect_equal(length(res56), 6)

  res57 <- col_as_mat1_(2L)
  expect_type(res57, "list")
  expect_equal(cbind(
    res57[[1]][, 1], res57[[2]][, 1], res57[[3]][, 1],
    res57[[4]][, 1]
  ), res57[[5]])

  res58 <- row_as_mat1_(2L)
  expect_type(res58, "list")
  expect_equal(rbind(
    res58[[1]][1, ], res58[[2]][1, ], res58[[3]][1, ],
    res58[[4]][1, ]
  ), res58[[5]])

  res60 <- transpose1_(2L)
  expect_type(res60, "double")
  expect_equal(dim(res60), c(3, 2))
})

test_that("official documentation - 3 (sparse)", {
  skip_if_no_sparse()

  res51 <- iterators3_(2L)
  expect_type(res51, "double")
  expect_equal(dim(res51), c(2, 4))

  res59 <- as_dense1_(2L)
  expect_type(res59, "double")
  expect_equal(length(res59), 2)
})
