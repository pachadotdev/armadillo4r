# sparse matrices copy works
local({
  if (!skip_if_no_sparse()) return(invisible(NULL))

  M <- Matrix::Matrix(c(0, 0, 0, 2, 6, 0, -1, 5, 0, 4, 3, 0, 0, 0, 5, 0),
    nrow = 4, ncol = 4, sparse = TRUE
  )

  N <- test_dgCMatrix_to_SpMat(M)

  expect_equal(N, M)
})

# as_SpMat accepts CsparseMatrix subclasses
local({
  if (!skip_if_no_sparse()) return(invisible(NULL))

  vals <- c(0, 0, 0, 2, 6, 0, -1, 5, 0, 4, 3, 0, 0, 0, 5, 0)
  M <- Matrix::Matrix(vals, nrow = 4, ncol = 4, sparse = TRUE)

  expect_equal(test_sparse_dims(M), c(4L, 4L))

  out <- test_sparse_to_dgCMatrix(M)
  expect_equal(class(out)[1], "dgCMatrix")
  expect_equal(as.matrix(out), as.matrix(M))
})

# as_SpMat accepts RsparseMatrix and TsparseMatrix
local({
  if (!skip_if_no_sparse()) return(invisible(NULL))

  M <- Matrix::Matrix(c(0, 0, 0, 2, 6, 0, -1, 5, 0, 4, 3, 0, 0, 0, 5, 0),
    nrow = 4, ncol = 4, sparse = TRUE
  )

  Mr <- as(M, "RsparseMatrix")
  Mt <- as(M, "TsparseMatrix")

  expect_equal(as.matrix(test_sparse_to_dgCMatrix(Mr)), as.matrix(M))
  expect_equal(as.matrix(test_sparse_to_dgCMatrix(Mt)), as.matrix(M))
})

# as_SpMat expands symmetric sparse matrices
local({
  if (!skip_if_no_sparse()) return(invisible(NULL))

  S <- Matrix::sparseMatrix(
    i = c(1L, 2L, 3L),
    j = c(1L, 1L, 3L),
    x = c(2, 3, 5),
    dims = c(3L, 3L),
    symmetric = TRUE
  )

  out <- test_sparse_to_dgCMatrix(S)
  expect_equal(class(out)[1], "dgCMatrix")
  expect_equal(as.matrix(out), as.matrix(S))
})

# as_SpMat materializes unit diagonal of triangular matrices
local({
  if (!skip_if_no_sparse()) return(invisible(NULL))

  # Strictly lower-triangular storage with diag = "U" means the diagonal is
  # implicitly 1; no diagonal entry may appear in `i`/`x` for the class to
  # validate.
  T <- new("dtCMatrix",
    i = c(1L, 2L, 2L),
    p = c(0L, 2L, 3L, 3L),
    x = c(4, 7, 5),
    Dim = c(3L, 3L),
    uplo = "L",
    diag = "U"
  )

  out <- test_sparse_to_dgCMatrix(T)
  expect_equal(class(out)[1], "dgCMatrix")
  expect_equal(as.matrix(out), as.matrix(T))
})
