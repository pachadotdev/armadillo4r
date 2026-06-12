has_sparse_bridge <- function() {
  if (!requireNamespace("Matrix", quietly = TRUE)) {
    return(FALSE)
  }

  if (utils::packageVersion("Matrix") < "1.6-2") {
    return(FALSE)
  }

  if (!exists("test_dgCMatrix_to_SpMat", mode = "function")) {
    return(FALSE)
  }

  isTRUE(tryCatch({
    getNativeSymbolInfo(
      "_armadillo4rtest_test_dgCMatrix_to_SpMat",
      PACKAGE = "armadillo4rtest"
    )
    TRUE
  }, error = function(...) FALSE))
}

skip_if_no_sparse <- function() {
  has_sparse_bridge()
}
