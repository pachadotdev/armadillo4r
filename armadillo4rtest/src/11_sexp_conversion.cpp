#include "00_main.h"

[[cpp4r::register]] SEXP implicit_conversion_double(SEXP x) {
  arma::mat result = cpp4r::as_cpp<arma::mat>(x);
  return cpp4r::as_sexp(result);
}

[[cpp4r::register]] SEXP implicit_conversion_float(SEXP x) {
  arma::fmat result = cpp4r::as_cpp<arma::fmat>(x);
  return cpp4r::as_sexp(result);
}

[[cpp4r::register]] SEXP implicit_conversion_int(SEXP x) {
  arma::imat result = cpp4r::as_cpp<arma::imat>(x);
  return cpp4r::as_sexp(result);
}

[[cpp4r::register]] SEXP implicit_conversion_uint(SEXP x) {
  arma::umat result = cpp4r::as_cpp<arma::umat>(x);
  return cpp4r::as_sexp(result);
}
