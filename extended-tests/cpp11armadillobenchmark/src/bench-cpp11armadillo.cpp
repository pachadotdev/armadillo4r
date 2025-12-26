#include <cpp11.hpp>
#include <cpp11armadillo.hpp>
#include <cstring>
#include <vector>

using namespace cpp11;
using namespace arma;

inline bool rrc_(uvec &excluded, const mat &XtX, double tol) {
  const uword p = XtX.n_cols;
  excluded.zeros(p);

  if (p == 0) { return true; }

  mat R(p, p, fill::zeros);
  uword n_excluded = 0;

  for (uword j = 0; j < p; ++j) {
    double R_jj = XtX(j, j);

    if (j > 0) {
      // Get indices of active (non-excluded) prior columns
      uvec active = find(excluded.head(j) == 0);
      if (active.n_elem > 0) {
        vec R_col_j = vec(R.col(j));
        vec R_active_j = R_col_j.elem(active);
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

[[cpp11::register]] list rrc_cpp11_(const doubles_matrix<>& xtx,
                                                        double tol) {
  mat XtX = as_mat(xtx);
  uvec excluded;
  bool success = rrc_(excluded, XtX, tol);

  writable::list result;
  result.push_back({"excluded"_nm = as_integers(excluded)});
  result.push_back({"success"_nm = success});

  return result;
}
