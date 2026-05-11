skip_if_no_sparse <- function() {
  skip_if_not_installed("Matrix", minimum_version = "1.6-2")
  if (!exists("test_dgCMatrix_to_SpMat", mode = "function")) {
    skip("sparse matrix support not compiled (Matrix < 1.6-2 at build time)")
  }
}
