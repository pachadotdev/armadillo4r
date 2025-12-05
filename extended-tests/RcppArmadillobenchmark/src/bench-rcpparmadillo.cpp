#include <RcppArmadillo.h>
#include <cstring>
#include <vector>

using namespace Rcpp;

inline bool rrc_(arma::uvec &excluded, const arma::mat &XtX,
                                         double tol) {
  const size_t p = XtX.n_cols;
  excluded.zeros(p);

  if (p == 0)
    return true;

  arma::mat R(p, p, arma::fill::zeros);

  double *R_ptr = R.memptr();
  arma::uword *excluded_ptr = excluded.memptr();
  const double *XtX_ptr = XtX.memptr();

  size_t n_excluded = 0;

  for (size_t j = 0; j < p; ++j) {

    double R_jj = XtX_ptr[j + j * p];

    if (j > 0) {
      const double *R_j_ptr = R_ptr + j * p;
      for (size_t k = 0; k < j; ++k) {
        if (excluded_ptr[k] == 0) {
          double R_jk = R_j_ptr[k];
          R_jj -= R_jk * R_jk;
        }
      }
    }

    if (R_jj < tol) {
      excluded_ptr[j] = 1;
      n_excluded++;
      continue;
    }

    R_jj = std::sqrt(R_jj);
    R_ptr[j + j * p] = R_jj;
    const double inv_R_jj = 1.0 / R_jj;

    for (size_t col = j + 1; col < p; ++col) {
      double R_j_col = XtX_ptr[j + col * p];

      const double *R_col_ptr = R_ptr + col * p;
      const double *R_j_ptr = R_ptr + j * p;

      for (size_t k = 0; k < j; ++k) {
        if (excluded_ptr[k] == 0) {
          R_j_col -= R_j_ptr[k] * R_col_ptr[k];
        }
      }

      R_ptr[j + col * p] = R_j_col * inv_R_jj;
    }
  }

  return n_excluded < p;
}

// [[Rcpp::export]]
List rrc_rcpp_(NumericMatrix xtx, double tol) {
  arma::mat XtX = as<arma::mat>(xtx);
  arma::uvec excluded;
  bool success = rrc_(excluded, XtX, tol);

  IntegerVector excluded_r(excluded.n_elem);
  for (size_t i = 0; i < excluded.n_elem; ++i) {
    excluded_r[i] = excluded[i];
  }

  return List::create(
    Named("excluded") = excluded_r,
    Named("success") = success
  );
}
