#pragma once

using namespace arma;
using namespace cpp4r;

#ifndef SPARSEMATRICES_HPP
#define SPARSEMATRICES_HPP

////////////////////////////////////////////////////////////////
// R to Armadillo
////////////////////////////////////////////////////////////////

template <typename T>
inline SpMat<T> as_SpMat(const T& x) {
  // Generic implementation
  throw std::runtime_error("Cannot convert to SpMat");
}

template <typename T, typename U>
inline SpMat<T> dblint_matrix_to_SpMat_(const U& x) {
  const size_t n = x.nrow();
  const size_t m = x.ncol();

  SpMat<T> y(n, m);

  std::vector<std::pair<size_t, size_t>> non_zero_positions;

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      if (x(i, j) != 0) {
        non_zero_positions.emplace_back(i, j);
      }
    }
  }

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (size_t k = 0; k < non_zero_positions.size(); ++k) {
    const auto& pos = non_zero_positions[k];
    y(pos.first, pos.second) = x(pos.first, pos.second);
  }

  return y;
}

template <typename T, typename U>
inline SpMat<T> dblint_to_SpMat_(const U& x) {
  const size_t n = x.size();

  SpMat<T> y(n, 1);

#ifdef _OPENMP
#pragma omp parallel for schedule(static)
#endif
  for (size_t i = 0; i < n; ++i) {
    y(i, 0) = x[i];
  }

  return y;
}

inline SpMat<double> as_SpMat(const doubles_matrix<>& x) {
  return dblint_matrix_to_SpMat_<double, doubles_matrix<>>(x);
}

inline SpMat<int> as_SpMat(const integers_matrix<>& x) {
  return dblint_matrix_to_SpMat_<int, integers_matrix<>>(x);
}

inline SpMat<double> as_SpMat(const doubles& x) {
  return dblint_to_SpMat_<double, doubles>(x);
}

inline SpMat<int> as_SpMat(const integers& x) {
  return dblint_to_SpMat_<int, integers>(x);
}

inline SpMat<double> as_sp_dmat(const doubles_matrix<>& x) { return as_SpMat(x); }
inline SpMat<float> as_sp_fmat(const doubles_matrix<>& x) {
  SpMat<double> y = dblint_matrix_to_SpMat_<double, doubles_matrix<>>(x);
  return arma::conv_to<SpMat<float>>::from(y);
}

inline SpMat<uword> as_sp_umat(const integers_matrix<>& x) {
  SpMat<int> y = dblint_matrix_to_SpMat_<int, integers_matrix<>>(x);
  return arma::conv_to<SpMat<uword>>::from(y);
}

inline SpMat<sword> as_sp_imat(const integers_matrix<>& x) {
  SpMat<int> y = dblint_matrix_to_SpMat_<int, integers_matrix<>>(x);
  return arma::conv_to<SpMat<sword>>::from(y);
}

////////////////////////////////////////////////////////////////
// Armadillo to R
////////////////////////////////////////////////////////////////

// Double/Integer

template <typename T, typename U>
inline U SpMat_to_dblint_matrix_(const SpMat<T>& A) {
  const size_t n = A.n_rows;
  const size_t m = A.n_cols;

  using dblint_matrix =
      typename std::conditional<std::is_same<U, doubles_matrix<>>::value,
                                writable::doubles_matrix<>,
                                writable::integers_matrix<>>::type;

  dblint_matrix B(n, m);

  // Initialize to zero
  if constexpr (std::is_same<U, doubles_matrix<>>::value) {
    std::memset(REAL(B), 0, n * m * sizeof(double));
  } else {
    std::memset(INTEGER(B), 0, n * m * sizeof(int));
  }

  // Only iterate non-zero elements - O(nnz) instead of O(n*m)
  for (typename SpMat<T>::const_iterator it = A.begin(); it != A.end(); ++it) {
    B(it.row(), it.col()) = *it;
  }

  return B;
}

inline doubles_matrix<> as_doubles_matrix(const SpMat<double>& A) {
  return SpMat_to_dblint_matrix_<double, doubles_matrix<>>(A);
}

// Always provide for SpMat<int>
inline integers_matrix<> as_integers_matrix(const SpMat<int>& A) {
  return SpMat_to_dblint_matrix_<int, integers_matrix<>>(A);
}

inline doubles_matrix<> as_doubles_matrix(const SpMat<float>& A) {
  SpMat<double> B = arma::conv_to<SpMat<double>>::from(A);
  return as_doubles_matrix(B);
}

// Complex

template <typename T>
inline complexes_matrix<> SpMat_to_complexes_matrix_(const SpMat<T>& A) {
  const size_t n = A.n_rows;
  const size_t m = A.n_cols;

  writable::complexes_matrix<> B(n, m);

  // Initialize to zero
  Rcomplex* B_data = COMPLEX(B);
  std::memset(B_data, 0, n * m * sizeof(Rcomplex));

  // Only iterate non-zero elements
  for (typename SpMat<T>::const_iterator it = A.begin(); it != A.end(); ++it) {
    B(it.row(), it.col()) = *it;
  }

  return B;
}

inline complexes_matrix<> as_complexes_matrix(const SpMat<std::complex<double>>& A) {
  return SpMat_to_complexes_matrix_<std::complex<double>>(A);
}

#endif

////////////////////////////////////////////////////////////////
// dgCMatrix to Armadillo
////////////////////////////////////////////////////////////////

// reference:
// https://www.r-bloggers.com/2020/03/what-is-a-dgcmatrix-object-made-of-sparse-matrix-format-in-r/
// http://adv-r.had.co.nz/OO-essentials.html#s4

inline bool is_dgCMatrix(SEXP x) { return Rf_inherits(x, "dgCMatrix"); }

inline SpMat<double> as_SpMat(SEXP x) {
  if (!is_dgCMatrix(x)) {
    stop("Input is not a dgCMatrix");
  }

  // Cache slot symbols to avoid repeated lookups
  static SEXP i_sym = Rf_install("i");
  static SEXP p_sym = Rf_install("p");
  static SEXP x_sym = Rf_install("x");
  static SEXP Dim_sym = Rf_install("Dim");

  // Extract the slots from dgCMatrix (direct pointer access)
  const int* row_indices = INTEGER(R_do_slot(x, i_sym));
  const int* col_ptrs = INTEGER(R_do_slot(x, p_sym));
  const double* values = REAL(R_do_slot(x, x_sym));
  const int* dims = INTEGER(R_do_slot(x, Dim_sym));

  const uword n_rows = static_cast<uword>(dims[0]);
  const uword n_cols = static_cast<uword>(dims[1]);
  const uword nnz = static_cast<uword>(col_ptrs[n_cols]);

  // Convert to uvec/vec wrapping the data (zero-copy where possible)
  // Note: row_indices are 0-based in dgCMatrix, same as Armadillo
  uvec rowind(nnz);
  for (uword i = 0; i < nnz; ++i) {
    rowind[i] = static_cast<uword>(row_indices[i]);
  }

  uvec colptr(n_cols + 1);
  for (uword j = 0; j <= n_cols; ++j) {
    colptr[j] = static_cast<uword>(col_ptrs[j]);
  }

  // Values can be wrapped directly (same type)
  vec vals(const_cast<double*>(values), nnz, false, false);

  // Construct SpMat directly from CSC components
  return SpMat<double>(rowind, colptr, vals, n_rows, n_cols);
}

////////////////////////////////////////////////////////////////
// SpMat to dgCMatrix
////////////////////////////////////////////////////////////////

inline SEXP as_dgCMatrix(const SpMat<double>& A) {
  const uword n_rows = A.n_rows;
  const uword n_cols = A.n_cols;
  const uword nnz = A.n_nonzero;

  // Armadillo SpMat is already in CSC format - direct access to internal arrays
  // A.row_indices: row indices (0-based, same as dgCMatrix)
  // A.col_ptrs: column pointers
  // A.values: non-zero values

  // Create R vectors for dgCMatrix slots
  SEXP i_sexp = PROTECT(Rf_allocVector(INTSXP, nnz));       // row indices
  SEXP p_sexp = PROTECT(Rf_allocVector(INTSXP, n_cols + 1)); // column pointers
  SEXP x_sexp = PROTECT(Rf_allocVector(REALSXP, nnz));      // values
  SEXP Dim_sexp = PROTECT(Rf_allocVector(INTSXP, 2));       // dimensions

  int* i_ptr = INTEGER(i_sexp);
  int* p_ptr = INTEGER(p_sexp);
  double* x_ptr = REAL(x_sexp);
  int* Dim_ptr = INTEGER(Dim_sexp);

  // Copy data directly from Armadillo's internal CSC storage
  const uword* row_ind = A.row_indices;
  const uword* col_ptr = A.col_ptrs;
  const double* vals = A.values;

  for (uword k = 0; k < nnz; ++k) {
    i_ptr[k] = static_cast<int>(row_ind[k]);
    x_ptr[k] = vals[k];
  }

  for (uword j = 0; j <= n_cols; ++j) {
    p_ptr[j] = static_cast<int>(col_ptr[j]);
  }

  Dim_ptr[0] = static_cast<int>(n_rows);
  Dim_ptr[1] = static_cast<int>(n_cols);

  // Create S4 object directly
  SEXP dgCMatrix_class = PROTECT(R_do_MAKE_CLASS("dgCMatrix"));
  SEXP result = PROTECT(R_do_new_object(dgCMatrix_class));

  // Set slots using cached symbols
  static SEXP i_sym = Rf_install("i");
  static SEXP p_sym = Rf_install("p");
  static SEXP x_sym = Rf_install("x");
  static SEXP Dim_sym = Rf_install("Dim");

  R_do_slot_assign(result, i_sym, i_sexp);
  R_do_slot_assign(result, p_sym, p_sexp);
  R_do_slot_assign(result, x_sym, x_sexp);
  R_do_slot_assign(result, Dim_sym, Dim_sexp);

  UNPROTECT(6);
  return result;
}
