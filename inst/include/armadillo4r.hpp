#pragma once

#ifdef _OPENMP
#include <omp.h>
#endif

// clang-format off
#include <R.h>
#include <R_ext/Random.h>
#include <Rmath.h>
#include <cpp4r.hpp>
#include <armadillo4r/armadillo.hpp>
#include <armadillo4r/wrappers/matrices.hpp>
#include <armadillo4r/wrappers/sparse_matrices.hpp>
#include <armadillo4r/wrappers/vectors.hpp>
// clang-format on

using mat = arma::mat;
using fmat = arma::fmat;
using imat = arma::imat;
using umat = arma::umat;
using vec = arma::vec;
using ivec = arma::ivec;
using uvec = arma::uvec;
using fvec = arma::fvec;
using rowvec = arma::rowvec;
using irowvec = arma::irowvec;
using urowvec = arma::urowvec;
using frowvec = arma::frowvec;
using cube = arma::cube;
using icube = arma::icube;
using ucube = arma::ucube;
using fcube = arma::fcube;
using cx_mat = arma::cx_mat;
using cx_vec = arma::cx_vec;
using cx_rowvec = arma::cx_rowvec;
using cx_cube = arma::cx_cube;

////////////////////////////////////////////////////////////////////////////////

// Custom RNG class to ensure synchronization with R's RNG state

class arma_rng_alt {
 public:
  typedef unsigned int seed_type;

  inline static void set_seed(const seed_type val) {
    (void)val;  // No-op, cannot set seed in R from C++ code
  }

  arma_inline static int randi_val() { return static_cast<int>(::Rf_runif(0, RAND_MAX)); }

  arma_inline static double randu_val() { return ::Rf_runif(0, 1); }

  inline static double randn_val() {
    double u1, u2, s;
    do {
      u1 = 2.0 * ::Rf_runif(0, 1) - 1.0;
      u2 = 2.0 * ::Rf_runif(0, 1) - 1.0;
      s = u1 * u1 + u2 * u2;
    } while (s >= 1.0);
    return u1 * std::sqrt((-2.0 * std::log(s)) / s);
  }

  template <typename eT>
  inline static void randi_fill(eT* mem, const arma::uword N, const int a, const int b) {
    const arma::uword length = b - a + 1;
    const double scale = static_cast<double>(length) / RAND_MAX;
    for (arma::uword i = 0; i < N; ++i) {
      mem[i] = std::min(b, static_cast<int>(::Rf_runif(0, RAND_MAX) * scale) + a);
    }
  }

  inline static int randi_max_val() { return RAND_MAX; }
};

////////////////////////////////////////////////////////////////////////////////

// Main RNG class that uses arma_rng_alt for RNG operations

class arma_rng {
 public:
  typedef arma_rng_alt::seed_type seed_type;

  static constexpr int rng_method = 2;

  inline static void set_seed(const seed_type val) { arma_rng_alt::set_seed(val); }

  inline static void set_seed_random() {
    cpp4r::stop(
        "When called from R, the RNG seed has to be set at the R level via set.seed()");
  }

  template <typename eT>
  struct randi {
    inline operator eT() { return eT(arma_rng_alt::randi_val()); }

    inline static int max_val() { return arma_rng_alt::randi_max_val(); }

    inline static void fill(eT* mem, const arma::uword N, const int a, const int b) {
      arma_rng_alt::randi_fill(mem, N, a, b);
    }
  };

  template <typename eT>
  struct randu {
    inline operator eT() { return eT(arma_rng_alt::randu_val()); }

    inline static void fill(eT* mem, const arma::uword N) {
      for (arma::uword i = 0; i < N; ++i) {
        mem[i] = eT(arma_rng_alt::randu_val());
      }
    }

    inline static void fill(eT* mem, const arma::uword N, const double a,
                            const double b) {
      const double r = b - a;
      for (arma::uword i = 0; i < N; ++i) {
        mem[i] = eT(arma_rng_alt::randu_val() * r + a);
      }
    }
  };

  template <typename eT>
  struct randn {
    inline operator eT() const { return eT(arma_rng_alt::randn_val()); }

    inline static void fill(eT* mem, const arma::uword N) {
      for (arma::uword i = 0; i < N; ++i) {
        mem[i] = eT(arma_rng_alt::randn_val());
      }
    }

    inline static void fill(eT* mem, const arma::uword N, const double mu,
                            const double sd) {
      for (arma::uword i = 0; i < N; ++i) {
        const eT val = eT(arma_rng_alt::randn_val());
        mem[i] = (val * sd) + mu;
      }
    }
  };
};

////////////////////////////////////////////////////////////////////////////////

namespace cpp4r {

// Specializations for as_cpp - converting from R objects to Armadillo types

template <>
inline arma::mat as_cpp<arma::mat>(SEXP x) {
  // Handle both integer and double matrices
  if (TYPEOF(x) == INTSXP) {
    cpp4r::integers_matrix<> temp = cpp4r::as_cpp<cpp4r::integers_matrix<>>(x);
    arma::Mat<int> imat = ::as_Mat(temp);
    return arma::conv_to<arma::mat>::from(imat);
  } else {
    return ::as_Mat(cpp4r::as_cpp<cpp4r::doubles_matrix<>>(x));
  }
}

template <>
inline arma::fmat as_cpp<arma::fmat>(SEXP x) {
  // Handle both integer and double matrices
  if (TYPEOF(x) == INTSXP) {
    cpp4r::integers_matrix<> temp = cpp4r::as_cpp<cpp4r::integers_matrix<>>(x);
    arma::Mat<int> imat = ::as_Mat(temp);
    return arma::conv_to<arma::fmat>::from(imat);
  } else {
    return ::as_fmat(cpp4r::as_cpp<cpp4r::doubles_matrix<>>(x));
  }
}

template <>
inline arma::imat as_cpp<arma::imat>(SEXP x) {
  // Handle both integer and double matrices
  if (TYPEOF(x) == REALSXP) {
    cpp4r::doubles_matrix<> temp = cpp4r::as_cpp<cpp4r::doubles_matrix<>>(x);
    arma::mat dmat = ::as_Mat(temp);
    return arma::conv_to<arma::imat>::from(dmat);
  } else {
    return ::as_imat(cpp4r::as_cpp<cpp4r::integers_matrix<>>(x));
  }
}

template <>
inline arma::umat as_cpp<arma::umat>(SEXP x) {
  // Handle both integer and double matrices
  if (TYPEOF(x) == REALSXP) {
    cpp4r::doubles_matrix<> temp = cpp4r::as_cpp<cpp4r::doubles_matrix<>>(x);
    arma::mat dmat = ::as_Mat(temp);
    return arma::conv_to<arma::umat>::from(dmat);
  } else {
    return ::as_umat(cpp4r::as_cpp<cpp4r::integers_matrix<>>(x));
  }
}

template <>
inline arma::vec as_cpp<arma::vec>(SEXP x) {
  // Handle both integer and double vectors
  if (TYPEOF(x) == INTSXP) {
    cpp4r::integers temp = cpp4r::as_cpp<cpp4r::integers>(x);
    arma::Col<int> icol = ::as_Col(temp);
    return arma::conv_to<arma::vec>::from(icol);
  } else {
    return ::as_Col(cpp4r::as_cpp<cpp4r::doubles>(x));
  }
}

template <>
inline arma::ivec as_cpp<arma::ivec>(SEXP x) {
  // Handle both integer and double vectors
  if (TYPEOF(x) == REALSXP) {
    cpp4r::doubles temp = cpp4r::as_cpp<cpp4r::doubles>(x);
    arma::vec dvec = ::as_Col(temp);
    return arma::conv_to<arma::ivec>::from(dvec);
  } else {
    cpp4r::integers temp = cpp4r::as_cpp<cpp4r::integers>(x);
    arma::Col<int> temp_col = ::as_Col(temp);
    return arma::conv_to<arma::ivec>::from(temp_col);
  }
}

template <>
inline arma::uvec as_cpp<arma::uvec>(SEXP x) {
  // Handle both integer and double vectors
  if (TYPEOF(x) == REALSXP) {
    cpp4r::doubles temp = cpp4r::as_cpp<cpp4r::doubles>(x);
    arma::vec dvec = ::as_Col(temp);
    return arma::conv_to<arma::uvec>::from(dvec);
  } else {
    arma::ivec temp = as_cpp<arma::ivec>(x);
    return arma::conv_to<arma::uvec>::from(temp);
  }
}

template <>
inline arma::fvec as_cpp<arma::fvec>(SEXP x) {
  // Handle both integer and double vectors
  if (TYPEOF(x) == INTSXP) {
    cpp4r::integers temp = cpp4r::as_cpp<cpp4r::integers>(x);
    arma::Col<int> icol = ::as_Col(temp);
    return arma::conv_to<arma::fvec>::from(icol);
  } else {
    arma::vec temp = as_cpp<arma::vec>(x);
    return arma::conv_to<arma::fvec>::from(temp);
  }
}

template <>
inline arma::rowvec as_cpp<arma::rowvec>(SEXP x) {
  arma::vec temp = as_cpp<arma::vec>(x);
  return temp.t();
}

template <>
inline arma::irowvec as_cpp<arma::irowvec>(SEXP x) {
  arma::ivec temp = as_cpp<arma::ivec>(x);
  return temp.t();
}

template <>
inline arma::urowvec as_cpp<arma::urowvec>(SEXP x) {
  arma::uvec temp = as_cpp<arma::uvec>(x);
  return temp.t();
}

template <>
inline arma::frowvec as_cpp<arma::frowvec>(SEXP x) {
  arma::fvec temp = as_cpp<arma::fvec>(x);
  return temp.t();
}

// Specializations for as_sexp - converting from Armadillo types to R objects

template <>
inline SEXP as_sexp(const arma::mat& x) {
  return ::as_doubles_matrix(x);
}

template <>
inline SEXP as_sexp(const arma::fmat& x) {
  arma::mat temp = arma::conv_to<arma::mat>::from(x);
  return ::as_doubles_matrix(temp);
}

template <>
inline SEXP as_sexp(const arma::imat& x) {
  return ::as_integers_matrix(x);
}

template <>
inline SEXP as_sexp(const arma::umat& x) {
  arma::Mat<int> temp = arma::conv_to<arma::Mat<int>>::from(x);
  return ::as_integers_matrix(temp);
}

template <>
inline SEXP as_sexp(const arma::vec& x) {
  return ::as_doubles_matrix(x);
}

template <>
inline SEXP as_sexp(const arma::ivec& x) {
  return ::as_integers_matrix(x);
}

template <>
inline SEXP as_sexp(const arma::uvec& x) {
  arma::Col<int> temp = arma::conv_to<arma::Col<int>>::from(x);
  return ::as_integers_matrix(temp);
}

template <>
inline SEXP as_sexp(const arma::fvec& x) {
  arma::vec temp = arma::conv_to<arma::vec>::from(x);
  return ::as_doubles_matrix(temp);
}

template <>
inline SEXP as_sexp(const arma::rowvec& x) {
  return ::as_doubles_matrix(x);
}

template <>
inline SEXP as_sexp(const arma::irowvec& x) {
  return ::as_integers_matrix(x);
}

template <>
inline SEXP as_sexp(const arma::urowvec& x) {
  arma::Row<int> temp = arma::conv_to<arma::Row<int>>::from(x);
  return ::as_integers_matrix(temp);
}

template <>
inline SEXP as_sexp(const arma::frowvec& x) {
  arma::rowvec temp = arma::conv_to<arma::rowvec>::from(x);
  return ::as_doubles_matrix(temp);
}

}  // namespace cpp4r

////////////////////////////////////////////////////////////////////////////////

// Implicit conversion helpers for seamless integration
// These allow automatic conversion from cpp4r types to Armadillo types
//
// Usage patterns:
//
// 1. Using wrapper classes (recommended for function parameters):
//    vec ols_fit(const armadillo4r::mat_wrapper& X, const armadillo4r::vec_wrapper& Y) {
//      // X and Y can be used directly as arma::mat and arma::vec
//      mat Q, R;
//      qr_econ(Q, R, X);
//      return solve(trimatu(R), Q.t() * Y);
//    }
//    [[cpp4r::register]] doubles ols_(const doubles_matrix<>& x, const doubles& y) {
//      return cpp4r::as_sexp(ols_fit(x, y));  // automatic conversion
//    }
//
// 2. Using as_arma() helper function (for explicit conversion):
//    vec ols_fit(const Mat<double>& X, const Col<double>& Y) {
//      mat Q, R;
//      qr_econ(Q, R, X);
//      return solve(trimatu(R), Q.t() * Y);
//    }
//    [[cpp4r::register]] doubles ols_(const doubles_matrix<>& x, const doubles& y) {
//      return cpp4r::as_sexp(ols_fit(as_arma(x), as_arma(y)));
//    }
//
// 3. Traditional approach (still supported):
//    [[cpp4r::register]] doubles ols_(const doubles_matrix<>& x, const doubles& y) {
//      mat X = as_Mat(x);
//      vec Y = as_Col(y);
//      return as_doubles(ols_fit(X, Y));
//    }
//
// Note on ambiguity:
// - Wrapper classes inherit from Armadillo types, so they can be passed anywhere
//   an Armadillo type is expected without ambiguity.
// - as_arma() provides explicit conversion when you prefer clarity or need to
//   handle edge cases.
// - The traditional approach gives you full control over the conversion process.
//
// Conversion mappings:
// - doubles_matrix<> <-> Mat<double> (arma::mat)
// - integers_matrix<> <-> Mat<int> (arma::imat) or Mat<uword> (arma::umat)
// - doubles <-> Col<double> (arma::vec)
// - integers <-> Col<int> (arma::ivec) or Col<uword> (arma::uvec)
// - complexes_matrix<> <-> Mat<std::complex<double>> (arma::cx_mat)
// - complexes <-> Col<std::complex<double>> (arma::cx_vec)

namespace armadillo4r {

// Helper class to enable implicit conversions from cpp4r::doubles_matrix<> to arma::mat
struct mat_wrapper : public arma::mat {
  mat_wrapper(const cpp4r::doubles_matrix<>& x) : arma::mat(::as_Mat(x)) {}
  mat_wrapper(const arma::mat& x) : arma::mat(x) {}
  template <typename T>
  mat_wrapper(const arma::Mat<T>& x) : arma::mat(arma::conv_to<arma::mat>::from(x)) {}
};

// Helper class to enable implicit conversions from cpp4r::integers_matrix<> to arma::imat
struct imat_wrapper : public arma::imat {
  imat_wrapper(const cpp4r::integers_matrix<>& x) : arma::imat(::as_imat(x)) {}
  imat_wrapper(const arma::imat& x) : arma::imat(x) {}
  imat_wrapper(const cpp4r::doubles_matrix<>& x) {
    arma::mat temp = ::as_Mat(x);
    *this = arma::conv_to<arma::imat>::from(temp);
  }
};

// Helper class to enable implicit conversions from cpp4r::integers_matrix<> to arma::umat
struct umat_wrapper : public arma::umat {
  umat_wrapper(const cpp4r::integers_matrix<>& x) : arma::umat(::as_umat(x)) {}
  umat_wrapper(const arma::umat& x) : arma::umat(x) {}
  umat_wrapper(const cpp4r::doubles_matrix<>& x) {
    arma::mat temp = ::as_Mat(x);
    *this = arma::conv_to<arma::umat>::from(temp);
  }
};

// Helper class to enable implicit conversions from cpp4r::doubles_matrix<> to arma::fmat
struct fmat_wrapper : public arma::fmat {
  fmat_wrapper(const cpp4r::doubles_matrix<>& x) : arma::fmat(::as_fmat(x)) {}
  fmat_wrapper(const arma::fmat& x) : arma::fmat(x) {}
  fmat_wrapper(const cpp4r::integers_matrix<>& x) {
    arma::imat temp = ::as_imat(x);
    *this = arma::conv_to<arma::fmat>::from(temp);
  }
};

// Helper class to enable implicit conversions from cpp4r::doubles to arma::vec
struct vec_wrapper : public arma::vec {
  vec_wrapper(const cpp4r::doubles& x) : arma::vec(::as_Col(x)) {}
  vec_wrapper(const cpp4r::integers& x) {
    arma::Col<int> temp = ::as_Col(x);
    *this = arma::conv_to<arma::vec>::from(temp);
  }
  vec_wrapper(const arma::vec& x) : arma::vec(x) {}
};

// Helper class to enable implicit conversions from cpp4r::integers to arma::ivec
struct ivec_wrapper : public arma::ivec {
  ivec_wrapper(const cpp4r::integers& x) {
    arma::Col<int> temp = ::as_Col(x);
    *this = arma::conv_to<arma::ivec>::from(temp);
  }
  ivec_wrapper(const cpp4r::doubles& x) {
    arma::vec temp = ::as_Col(x);
    *this = arma::conv_to<arma::ivec>::from(temp);
  }
  ivec_wrapper(const arma::ivec& x) : arma::ivec(x) {}
};

// Helper class to enable implicit conversions from cpp4r::integers to arma::uvec
struct uvec_wrapper : public arma::uvec {
  uvec_wrapper(const cpp4r::integers& x) {
    arma::Col<int> temp = ::as_Col(x);
    *this = arma::conv_to<arma::uvec>::from(temp);
  }
  uvec_wrapper(const cpp4r::doubles& x) {
    arma::vec temp = ::as_Col(x);
    *this = arma::conv_to<arma::uvec>::from(temp);
  }
  uvec_wrapper(const arma::uvec& x) : arma::uvec(x) {}
};

// Helper class to enable implicit conversions from cpp4r::doubles to arma::fvec
struct fvec_wrapper : public arma::fvec {
  fvec_wrapper(const cpp4r::doubles& x) {
    arma::vec temp = ::as_Col(x);
    *this = arma::conv_to<arma::fvec>::from(temp);
  }
  fvec_wrapper(const cpp4r::integers& x) {
    arma::Col<int> temp = ::as_Col(x);
    *this = arma::conv_to<arma::fvec>::from(temp);
  }
  fvec_wrapper(const arma::fvec& x) : arma::fvec(x) {}
};

// Helper class to enable implicit conversions from cpp4r::complexes_matrix<> to arma::cx_mat
struct cx_mat_wrapper : public arma::cx_mat {
  cx_mat_wrapper(const cpp4r::complexes_matrix<>& x) {
    const int n = x.nrow();
    const int m = x.ncol();
    this->set_size(n, m);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        (*this)(i, j) = x(i, j);
      }
    }
  }
  cx_mat_wrapper(const arma::cx_mat& x) : arma::cx_mat(x) {}
};

// Helper class to enable implicit conversions from cpp4r::complexes to arma::cx_vec
struct cx_vec_wrapper : public arma::cx_vec {
  cx_vec_wrapper(const cpp4r::complexes& x) {
    const int n = x.size();
    this->set_size(n);
    for (int i = 0; i < n; ++i) {
      (*this)(i) = x[i];
    }
  }
  cx_vec_wrapper(const arma::cx_vec& x) : arma::cx_vec(x) {}
};

}  // namespace armadillo4r

////////////////////////////////////////////////////////////////////////////////

// Global overloads for seamless conversion in function parameters
// These enable: vec ols_fit(const Mat<double>& X, const Col<double>& Y)
// to be called with: ols_fit(doubles_matrix, doubles)

// Overload for Mat<double> from doubles_matrix<>
inline arma::Mat<double> as_arma(const cpp4r::doubles_matrix<>& x) {
  return ::as_Mat(x);
}

// Overload for Mat<int> from integers_matrix<>
inline arma::Mat<int> as_arma(const cpp4r::integers_matrix<>& x) {
  return ::as_Mat(x);
}

// Overload for Col<double> from doubles
inline arma::Col<double> as_arma(const cpp4r::doubles& x) {
  return ::as_Col(x);
}

// Overload for Col<int> from integers
inline arma::Col<int> as_arma(const cpp4r::integers& x) {
  return ::as_Col(x);
}

// Overload for cx_mat from complexes_matrix<>
inline arma::cx_mat as_arma(const cpp4r::complexes_matrix<>& x) {
  const int n = x.nrow();
  const int m = x.ncol();
  arma::cx_mat result(n, m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      result(i, j) = x(i, j);
    }
  }
  return result;
}

// Overload for cx_vec from complexes
inline arma::cx_vec as_arma(const cpp4r::complexes& x) {
  const int n = x.size();
  arma::cx_vec result(n);
  for (int i = 0; i < n; ++i) {
    result(i) = x[i];
  }
  return result;
}

// Pass-through overloads for Armadillo types (for generic programming)
template <typename T>
inline const arma::Mat<T>& as_arma(const arma::Mat<T>& x) {
  return x;
}

template <typename T>
inline const arma::Col<T>& as_arma(const arma::Col<T>& x) {
  return x;
}

template <typename T>
inline const arma::Row<T>& as_arma(const arma::Row<T>& x) {
  return x;
}

template <typename T>
inline const arma::Cube<T>& as_arma(const arma::Cube<T>& x) {
  return x;
}

template <typename T>
inline const arma::SpMat<T>& as_arma(const arma::SpMat<T>& x) {
  return x;
}
