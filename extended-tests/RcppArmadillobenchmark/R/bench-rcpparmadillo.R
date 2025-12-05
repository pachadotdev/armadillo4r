#' @export
rrc_rcpp <- function(XtX, tol = 1e-9) {
  rrc_rcpp_(XtX, tol)
}
