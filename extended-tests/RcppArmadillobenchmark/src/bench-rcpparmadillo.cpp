#include <RcppArmadillo.h>
#include <cstring>
#include <vector>

using namespace Rcpp;

// [[Rcpp::export]]
arma::mat add_two_rcpp_(NumericMatrix a, NumericMatrix b) {
  arma::mat A = as<arma::mat>(a);
  arma::mat B = as<arma::mat>(b);

  arma::mat Z = A + B;

  return Z;
}

// [[Rcpp::export]]
arma::mat add_four_rcpp_(NumericMatrix a, NumericMatrix b, NumericMatrix c,
                         NumericMatrix d) {
  arma::mat A = as<arma::mat>(a);
  arma::mat B = as<arma::mat>(b);
  arma::mat C = as<arma::mat>(c);
  arma::mat D = as<arma::mat>(d);

  arma::mat Z = A + B + C + D;

  return Z;
}

// [[Rcpp::export]]
arma::mat multiply_four_rcpp_(NumericMatrix a, NumericMatrix b, NumericMatrix c,
                              NumericMatrix d) {
  arma::mat A = as<arma::mat>(a);
  arma::mat B = as<arma::mat>(b);
  arma::mat C = as<arma::mat>(c);
  arma::mat D = as<arma::mat>(d);

  arma::uword n = A.n_cols;
  arma::uword n5 = n / 5;
  arma::uword n10 = n / 10;
  arma::uword n15 = n / 15;
  arma::uword n20 = n / 20;

  arma::mat Z = A.submat(0, 0, n5 - 1, n5 - 1) * B.submat(0, 0, n5 - 1, n10 - 1) *
                C.submat(0, 0, n10 - 1, n15 - 1) * D.submat(0, 0, n15 - 1, n20 - 1);

  return Z;
}

// [[Rcpp::export]]
arma::mat submatrix_manipulation_rcpp_(NumericMatrix a, NumericMatrix b) {
  arma::mat A = as<arma::mat>(a);
  arma::mat B = as<arma::mat>(b);

  arma::mat Z = B;
  Z.row(Z.n_rows - 1) = A.row(0);

  return Z;
}

// [[Rcpp::export]]
double multi_operation_rcpp_(NumericMatrix a, NumericMatrix b, NumericMatrix c) {
  arma::mat A = as<arma::mat>(a);
  arma::mat B = as<arma::mat>(b);
  arma::mat C = as<arma::mat>(c);

  // Compute: t(A.col(0)) * inv(diagmat(B)) * C.col(0)
  // This is equivalent to: sum(A[i,0] * (1/B[i,i]) * C[i,0]) for i in 0..n-1
  arma::vec a_col = A.col(0);
  arma::vec b_diag = B.diag();
  arma::vec c_col = C.col(0);

  double Z = as_scalar(a_col.t() * (c_col / b_diag));

  return Z;
}
