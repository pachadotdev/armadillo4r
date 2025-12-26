#include <RcppArmadillo.h>
#include <cstring>
#include <vector>

using namespace Rcpp;
using namespace RcppArmadillo;

inline bool rrc_(arma::uvec &excluded, const arma::mat &XtX, double tol) {
  const arma::uword p = XtX.n_cols;
  excluded.zeros(p);

  if (p == 0) { return true; }

  arma::mat R(p, p, arma::fill::zeros);
  arma::uword n_excluded = 0;

  for (arma::uword j = 0; j < p; ++j) {
    double R_jj = XtX(j, j);

    if (j > 0) {
      // Get indices of active (non-excluded) prior columns
      arma::uvec active = find(excluded.head(j) == 0);
      if (active.n_elem > 0) {
        arma::vec R_col_j = vec(R.col(j));
        arma::vec R_active_j = R_col_j.elem(active);
        R_jj -= dot(R_active_j, R_active_j);
      }
    }

    if (R_jj < tol) {
      excluded(j) = 1;
      n_excluded++;
      continue;
    }

    R_jj = std::sqrt(R_jj);
    R(j, j) = R_jj;
    double inv_R_jj = 1.0 / R_jj;

    if (j + 1 < p) {
      // Get indices of active prior columns
      uvec active = find(excluded.head(j) == 0);

      // Update remaining row elements
      rowvec R_j_rest = XtX(j, span(j + 1, p - 1));

      if (active.n_elem > 0) {
        vec R_col_j = vec(R.col(j));
        vec R_active_j = R_col_j.elem(active);
        mat R_rest = mat(R.cols(j + 1, p - 1));
        mat R_active_rest = R_rest.rows(active);
        R_j_rest -= (R_active_j.t() * R_active_rest);
      }

      R(j, span(j + 1, p - 1)) = R_j_rest * inv_R_jj;
    }
  }

  return n_excluded < p;
}

// [[Rcpp::export]]
List rrc_rcpp_(NumericMatrix xtx, double tol) {
  arma::mat XtX = as<mat>(xtx);
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
