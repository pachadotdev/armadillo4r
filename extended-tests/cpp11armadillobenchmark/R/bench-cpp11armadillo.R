#' @export
rrc_cpp11 <- function(XtX, tol = 1e-9) {
  rrc_cpp11_(XtX, tol)
}
