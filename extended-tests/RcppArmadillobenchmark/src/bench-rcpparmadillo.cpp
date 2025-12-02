#include <RcppArmadillo.h>
#include <cstring>
#include <vector>

using namespace Rcpp;

// [[Rcpp::export]]
NumericMatrix add_two_rcpp_(NumericMatrix a, NumericMatrix b) {
  mat A = as<mat>(a);
  mat B = as<mat>(b);

  mat Z = A + B;

  return Z;
}

// [[Rcpp::export]]
NumericMatrix add_four_rcpp_(NumericMatrix a, NumericMatrix b, NumericMatrix c,
                             NumericMatrix d) {
  mat A = as<mat>(a);
  mat B = as<mat>(b);
  mat C = as<mat>(c);
  mat D = as<mat>(d);

  mat Z = A + B + C + D;

  return Z;
}

// [[Rcpp::export]]
NumericMatrix multiply_four_rcpp_(NumericMatrix a, NumericMatrix b, NumericMatrix c,
                                  NumericMatrix d) {
  mat A = as<mat>(a);
  mat B = as<mat>(b);
  mat C = as<mat>(c);
  mat D = as<mat>(d);

  uword n = A.n_cols;
  uword n5 = n / 5;
  uword n10 = n / 10;
  uword n15 = n / 15;
  uword n20 = n / 20;

  mat Z = A.submat(0, 0, n5 - 1, n5 - 1) * B.submat(0, 0, n5 - 1, n10 - 1) *
          C.submat(0, 0, n10 - 1, n15 - 1) * D.submat(0, 0, n15 - 1, n20 - 1);

  return Z;
}

// [[Rcpp::export]]
NumericMatrix submatrix_manipulation_rcpp_(NumericMatrix a, NumericMatrix b) {
  mat A = as<mat>(a);
  mat B = as<mat>(b);

  mat Z = B;
  Z.row(Z.n_rows - 1) = A.row(0);

  return Z;
}

// [[Rcpp::export]]
double multi_operation_rcpp_(NumericMatrix a, NumericMatrix b, NumericMatrix c) {
  mat A = as<mat>(a);
  mat B = as<mat>(b);
  mat C = as<mat>(c);

  mat Z = A.t() * inv(diagmat(B)) * C;

  return as_scalar(Z);
}
