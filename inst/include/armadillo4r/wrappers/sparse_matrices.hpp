#pragma once

#ifndef SPARSE_MATRICES_HPP
#define SPARSE_MATRICES_HPP

// Auto-detect the Matrix package's public C API headers. Downstream packages
// that want the dgCMatrix/CHOLMOD bridge need to add `LinkingTo: Matrix
// (>= 1.6-2)` to their own DESCRIPTION; that puts <Matrix/Matrix.h> on the
// include path and the bridge below is enabled automatically. Packages that
// only need the dense-matrix <-> SpMat conversions do not have to depend on
// Matrix at all.
//
// Manual overrides:
//   - define ARMADILLO4R_NO_MATRIX   to force-disable the bridge
//   - define ARMADILLO4R_USE_MATRIX  to force-enable the bridge
#if !defined(ARMADILLO4R_NO_MATRIX)
#if defined(ARMADILLO4R_USE_MATRIX)
#define ARMADILLO4R_HAVE_MATRIX 1
#elif defined(__has_include)
#if __has_include(<Matrix/Matrix.h>)
#define ARMADILLO4R_HAVE_MATRIX 1
#endif
#endif
#endif

#ifdef ARMADILLO4R_HAVE_MATRIX
// The stubs in <Matrix/stubs.c> are declared as `static inline` so that this
// header may be included from multiple translation units without
// multiple-definition errors.
#ifndef R_MATRIX_INLINE
#define R_MATRIX_INLINE static inline
#endif
#include <Matrix/Matrix.h>
#include <Matrix/stubs.c>
#endif

using namespace arma;
using namespace cpp4r;

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

// Helper: initialize sparse matrix output to zero (doubles specialization)
template <typename U>
inline void spmat_init_zero_(
    writable::doubles_matrix<>& B, size_t n, size_t m,
    typename std::enable_if<std::is_same<U, doubles_matrix<>>::value>::type* = 0) {
  std::memset(REAL(B), 0, n * m * sizeof(double));
}

// Helper: initialize sparse matrix output to zero (integers specialization)
template <typename U>
inline void spmat_init_zero_(
    writable::integers_matrix<>& B, size_t n, size_t m,
    typename std::enable_if<std::is_same<U, integers_matrix<>>::value>::type* = 0) {
  std::memset(INTEGER(B), 0, n * m * sizeof(int));
}

template <typename T, typename U>
inline U SpMat_to_dblint_matrix_(const SpMat<T>& A) {
  const size_t n = A.n_rows;
  const size_t m = A.n_cols;

  using dblint_matrix =
      typename std::conditional<std::is_same<U, doubles_matrix<>>::value,
                                writable::doubles_matrix<>,
                                writable::integers_matrix<>>::type;

  dblint_matrix B(n, m);

  // Initialize to zero using SFINAE helper
  spmat_init_zero_<U>(B, n, m);

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

////////////////////////////////////////////////////////////////
// Matrix package sparse classes <-> Armadillo SpMat
////////////////////////////////////////////////////////////////

#ifdef ARMADILLO4R_HAVE_MATRIX

// Process-wide cholmod_common, lazily initialized. C++ guarantees that the
// static local inside an inline function refers to a single object across
// translation units.
inline cholmod_common* armadillo4r_chm_common_() {
  static cholmod_common c;
  static bool initialized = false;
  if (!initialized) {
    M_cholmod_start(&c);
    initialized = true;
  }
  return &c;
}

// Check S4 class inheritance by calling methods::is(x, klass). Rf_inherits
// only matches exact strings in the "class" attribute and does not traverse
// the S4 virtual class hierarchy (so e.g. it returns FALSE for a dgCMatrix
// against "CsparseMatrix").
inline bool armadillo4r_is_(SEXP x, const char* klass) {
  SEXP call = PROTECT(Rf_lang3(Rf_install("is"), x, Rf_mkString(klass)));
  SEXP methods_ns = PROTECT(R_FindNamespace(Rf_mkString("methods")));
  SEXP res = PROTECT(Rf_eval(call, methods_ns));
  const bool out = Rf_asLogical(res) == TRUE;
  UNPROTECT(3);
  return out;
}

// Coerce any sparse Matrix object (RsparseMatrix, TsparseMatrix, ...) to a
// CsparseMatrix by calling methods::as() at the R level. The returned SEXP
// is unprotected; the caller must PROTECT it.
inline SEXP armadillo4r_as_CsparseMatrix_(SEXP x) {
  SEXP call = PROTECT(Rf_lang3(Rf_install("as"), x, Rf_mkString("CsparseMatrix")));
  SEXP methods_ns = PROTECT(R_FindNamespace(Rf_mkString("methods")));
  SEXP res = Rf_eval(call, methods_ns);
  UNPROTECT(2);
  return res;
}

inline bool is_dgCMatrix(SEXP x) { return Rf_inherits(x, "dgCMatrix"); }

// Internal: build a SpMat<double> from a CsparseMatrix SEXP using the Matrix
// CHOLMOD bridge. Handles symmetric (stype != 0) and unit-triangular inputs.
inline SpMat<double> as_SpMat_from_Csparse_(SEXP x) {
  cholmod_common* c = armadillo4r_chm_common_();

  cholmod_sparse chol_stack;
  // checkUnit = TRUE: materialize implicit unit diagonal for triangular
  // matrices. sortInPlace = FALSE: never mutate the caller's data.
  CHM_SP A = M_sexp_as_cholmod_sparse(&chol_stack, x, TRUE, FALSE);
  if (A == nullptr) {
    stop("Could not interpret object as a CsparseMatrix");
  }

  if (A->xtype != CHOLMOD_REAL || A->dtype != CHOLMOD_DOUBLE) {
    stop("Sparse matrix must be real and double precision");
  }
  if (A->itype != CHOLMOD_INT) {
    stop("Sparse matrix must use 32-bit integer indices");
  }

  // For symmetric storage (stype != 0) expand to general form so the
  // resulting SpMat has both triangles populated.
  CHM_SP A_owned = nullptr;
  CHM_SP A_use = A;
  if (A->stype != 0) {
    A_owned = M_cholmod_copy(A, 0 /* stype = general */, 1 /* mode = numeric */, c);
    if (A_owned == nullptr) {
      stop("CHOLMOD failed to expand symmetric sparse matrix");
    }
    A_use = A_owned;
  }

  const uword n_rows = static_cast<uword>(A_use->nrow);
  const uword n_cols = static_cast<uword>(A_use->ncol);
  const int* Ap = static_cast<const int*>(A_use->p);
  const int* Ai = static_cast<const int*>(A_use->i);
  const double* Ax = static_cast<const double*>(A_use->x);
  const uword nnz = static_cast<uword>(Ap[n_cols]);

  uvec rowind(nnz);
  for (uword k = 0; k < nnz; ++k) {
    rowind[k] = static_cast<uword>(Ai[k]);
  }
  uvec colptr(n_cols + 1);
  for (uword j = 0; j <= n_cols; ++j) {
    colptr[j] = static_cast<uword>(Ap[j]);
  }
  vec vals(const_cast<double*>(Ax), nnz, true /* copy */, false);

  SpMat<double> out(rowind, colptr, vals, n_rows, n_cols);

  if (A_owned != nullptr) {
    M_cholmod_free_sparse(&A_owned, c);
  }
  return out;
}

// Accept any sparse Matrix object: CsparseMatrix subclasses go through the
// CHOLMOD bridge directly; RsparseMatrix / TsparseMatrix are coerced to
// CsparseMatrix at the R level first.
inline SpMat<double> as_SpMat(SEXP x) {
  if (armadillo4r_is_(x, "CsparseMatrix")) {
    return as_SpMat_from_Csparse_(x);
  }
  if (armadillo4r_is_(x, "sparseMatrix")) {
    SEXP coerced = PROTECT(armadillo4r_as_CsparseMatrix_(x));
    SpMat<double> out = as_SpMat_from_Csparse_(coerced);
    UNPROTECT(1);
    return out;
  }
  stop(
      "Input must be a sparse matrix from the 'Matrix' package "
      "(CsparseMatrix, RsparseMatrix, or TsparseMatrix)");
}

// Convert SpMat<double> to a dgCMatrix via M_cholmod_sparse_as_sexp. The
// uword -> int copy is unavoidable because dgCMatrix stores int indices.
inline SEXP as_dgCMatrix(const SpMat<double>& A) {
  cholmod_common* c = armadillo4r_chm_common_();

  const uword n_rows = A.n_rows;
  const uword n_cols = A.n_cols;
  const uword nnz = A.n_nonzero;

  CHM_SP B = M_cholmod_allocate_sparse(
      static_cast<size_t>(n_rows), static_cast<size_t>(n_cols), static_cast<size_t>(nnz),
      1 /* sorted */, 1 /* packed */, 0 /* stype = general */,
      CHOLMOD_REAL + CHOLMOD_DOUBLE, c);
  if (B == nullptr) {
    stop("CHOLMOD failed to allocate sparse matrix");
  }

  int* Bp = static_cast<int*>(B->p);
  int* Bi = static_cast<int*>(B->i);
  double* Bx = static_cast<double*>(B->x);

  const uword* row_ind = A.row_indices;
  const uword* col_ptr = A.col_ptrs;
  const double* vals = A.values;

  for (uword k = 0; k < nnz; ++k) {
    Bi[k] = static_cast<int>(row_ind[k]);
    Bx[k] = vals[k];
  }
  for (uword j = 0; j <= n_cols; ++j) {
    Bp[j] = static_cast<int>(col_ptr[j]);
  }

  // doFree = -1: free B with M_cholmod_free_sparse after the SEXP is built.
  return M_cholmod_sparse_as_sexp(B, -1, 0 /* general */, 0 /* numeric */, "" /* diag */,
                                  R_NilValue);
}

#endif  // ARMADILLO4R_HAVE_MATRIX

#endif
