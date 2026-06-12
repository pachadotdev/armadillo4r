#' @keywords internal
"_PACKAGE"

#' Check that cpp4r can be used
#' @keywords internal
#' @return integer value
check_cpp4r <- function() {
  # check cpp4r version
  finp <- system.file("include/cpp4r/version.hpp", package = "cpp4r")
  if (finp == "") {
    stop("cpp4r is not installed. Please install it with install.packages('cpp4r')", call. = FALSE)
  }
  return(invisible())
}

is_interactive <- function() {
  opt <- getOption("rlang_interactive", NULL)
  if (!is.null(opt)) {
    return(opt)
  }
  if (isTRUE(getOption("knitr.in.progress"))) {
    return(FALSE)
  }
  if (isTRUE(getOption("rstudio.notebook.executing"))) {
    return(FALSE)
  }
  if (identical(Sys.getenv("TESTTHAT"), "true")) {
    return(FALSE)
  }
  interactive()
}
