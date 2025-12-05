#include <armadillo4r.hpp>
#include <cpp4r.hpp>
#include <cstring>
#include <vector>

using namespace cpp4r;
using namespace arma;

inline bool rrc_(uvec &excluded, const mat &XtX, double tol) {
  const size_t p = XtX.n_cols;
  excluded.zeros(p);

  if (p == 0)
    return true;

  mat R(p, p, fill::zeros);

  double *R_ptr = R.memptr();
  uword *excluded_ptr = excluded.memptr();
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

/* roxygen
@title Rank-Revealing Cholesky
@export
*/
[[cpp4r::register]] list rrc_cpp4r(const doubles_matrix<>& xtx,
                                                       double tol) {
  mat XtX = as_mat(xtx);
  uvec excluded;
  bool success = rrc_(excluded, XtX, tol);

  writable::list result;
  result.push_back({"excluded"_nm = as_integers(excluded)});
  result.push_back({"success"_nm = success});

  return result;
}
