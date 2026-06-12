/* roxygen
@title Round-trip R matrix via arma::mat (double precision)
@param x numeric matrix
@return numeric matrix identical to input
@export
*/
[[cpp4r::register]] SEXP implicit_conversion_double(SEXP x) {
  arma::mat result = cpp4r::as_cpp<arma::mat>(x);
  return cpp4r::as_sexp(result);
}

/* roxygen
@title Round-trip R matrix via arma::fmat (single precision)
@param x numeric matrix
@return numeric matrix (values may differ slightly due to float precision)
@export
*/
[[cpp4r::register]] SEXP implicit_conversion_float(SEXP x) {
  arma::fmat result = cpp4r::as_cpp<arma::fmat>(x);
  return cpp4r::as_sexp(result);
}

/* roxygen
@title Round-trip R matrix via arma::imat (signed integer)
@param x integer or numeric matrix
@return integer matrix
@export
*/
[[cpp4r::register]] SEXP implicit_conversion_int(SEXP x) {
  arma::imat result = cpp4r::as_cpp<arma::imat>(x);
  return cpp4r::as_sexp(result);
}

/* roxygen
@title Round-trip R matrix via arma::umat (unsigned integer)
@param x integer or numeric matrix
@return integer matrix (values truncated to unsigned range)
@export
*/
[[cpp4r::register]] SEXP implicit_conversion_uint(SEXP x) {
  arma::umat result = cpp4r::as_cpp<arma::umat>(x);
  return cpp4r::as_sexp(result);
}
