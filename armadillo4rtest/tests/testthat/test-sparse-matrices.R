skip_if_no_sparse <- function() {
  skip_if_not_installed("Matrix", minimum_version = "1.6-2")
  if (!exists("test_dgCMatrix_to_SpMat", mode = "function")) {
    skip("sparse matrix support not compiled (Matrix < 1.6-2 at build time)")
  }
}

test_that("sparse matrices copy works", {
  skip_if_no_sparse()

  M <- Matrix::Matrix(c(0, 0, 0, 2, 6, 0, -1, 5, 0, 4, 3, 0, 0, 0, 5, 0),
    nrow = 4, ncol = 4, sparse = TRUE
  )

  N <- test_dgCMatrix_to_SpMat(M)

  expect_equal(N, M)
})

test_that("as_SpMat accepts CsparseMatrix subclasses", {
  skip_if_no_sparse()

  vals <- c(0, 0, 0, 2, 6, 0, -1, 5, 0, 4, 3, 0, 0, 0, 5, 0)
  M <- Matrix::Matrix(vals, nrow = 4, ncol = 4, sparse = TRUE)

  expect_equal(test_sparse_dims(M), c(4L, 4L))

  out <- test_sparse_to_dgCMatrix(M)
  expect_s4_class(out, "dgCMatrix")
  expect_equal(as.matrix(out), as.matrix(M))
})

test_that("as_SpMat accepts RsparseMatrix and TsparseMatrix", {
  skip_if_no_sparse()

  M <- Matrix::Matrix(c(0, 0, 0, 2, 6, 0, -1, 5, 0, 4, 3, 0, 0, 0, 5, 0),
    nrow = 4, ncol = 4, sparse = TRUE
  )

  Mr <- as(M, "RsparseMatrix")
  Mt <- as(M, "TsparseMatrix")

  expect_equal(as.matrix(test_sparse_to_dgCMatrix(Mr)), as.matrix(M))
  expect_equal(as.matrix(test_sparse_to_dgCMatrix(Mt)), as.matrix(M))
})

test_that("as_SpMat expands symmetric sparse matrices", {
  skip_if_no_sparse()

  S <- Matrix::sparseMatrix(
    i = c(1L, 2L, 3L),
    j = c(1L, 1L, 3L),
    x = c(2, 3, 5),
    dims = c(3L, 3L),
    symmetric = TRUE
  )

  out <- test_sparse_to_dgCMatrix(S)
  expect_s4_class(out, "dgCMatrix")
  expect_equal(as.matrix(out), as.matrix(S))
})

test_that("as_SpMat materializes unit diagonal of triangular matrices", {
  skip_if_no_sparse()

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
  expect_s4_class(out, "dgCMatrix")
  expect_equal(as.matrix(out), as.matrix(T))
})
