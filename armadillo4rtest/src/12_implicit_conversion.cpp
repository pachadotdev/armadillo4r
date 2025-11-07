#include "00_main.h"

// Example 1: Traditional approach (RECOMMENDED - safest)
// Always assign conversions to named variables to ensure proper lifetime

vec ols_fit2(const Mat<double>& X, const Col<double>& Y) {
  // QR decomposition
  mat Q, R;
  qr_econ(Q, R, X);

  // Least Squares Problem
  vec betas = solve(trimatu(R), Q.t() * Y);

  return betas;
}

[[cpp4r::register]] doubles ols_traditional_(const doubles_matrix<>& x,
                                             const doubles& y) {
  mat X = as_Mat(x);
  vec Y = as_Col(y);
  
  vec result = ols_fit2(X, Y);
  return as_doubles(result);
}

// Example 2: Simplified with as_doubles for return
// Still assign to named variables first for safety
// Note: cpp4r::as_sexp(vec) returns a matrix, not a vector, so use as_doubles

[[cpp4r::register]] doubles ols_simplified_(const doubles_matrix<>& x,
                                            const doubles& y) {
  mat X = as_mat(x);
  vec Y = as_Col(y);
  vec result = ols_fit2(X, Y);
  return as_doubles(result);
}

// Example 3: Matrix operations

[[cpp4r::register]] doubles_matrix<> matrix_add_(
    const doubles_matrix<>& a, const doubles_matrix<>& b) {
  Mat<double> A = as_Mat(a);
  mat B = as_mat(b);
  mat C = A + B;
  return cpp4r::as_sexp(C);
}

// Example 4: Integer matrix operations using as_imat

[[cpp4r::register]] integers_matrix<> integer_transpose_(
    const integers_matrix<>& x) {
  imat X = as_imat(x);
  imat Y = X.t();
  return cpp4r::as_sexp(Y);
}

// Example 5: Unsigned integer matrix using as_umat

[[cpp4r::register]] integers_matrix<> uvec_example_(const integers_matrix<>& x) {
  umat X = as_umat(x);
  umat Y = X + 1;
  return cpp4r::as_sexp(Y);
}

// Example 6: Float matrix using as_fmat

[[cpp4r::register]] doubles_matrix<> fmat_example_(const doubles_matrix<>& x) {
  fmat X = as_fmat(x);
  fmat Y = X * 2.0f;
  mat result = arma::conv_to<mat>::from(Y);
  return cpp4r::as_sexp(result);
}

// Example 7: Complex matrix operations

[[cpp4r::register]] complexes_matrix<> complex_multiply_(
    const complexes_matrix<>& a, const complexes_matrix<>& b) {
  // For complex matrices, manual conversion
  const int n = a.nrow();
  const int m = a.ncol();
  cx_mat A(n, m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      A(i, j) = a(i, j);
    }
  }
  
  cx_mat B(n, m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      B(i, j) = b(i, j);
    }
  }
  
  cx_mat C = A * B;
  return as_complexes_matrix(C);
}

// Example 8: Generic function with element-wise multiplication

template <typename T>
T element_wise_multiply(const T& A, const T& B) {
  return A % B;  // element-wise multiplication
}

[[cpp4r::register]] doubles_matrix<> generic_multiply_(
    const doubles_matrix<>& a, const doubles_matrix<>& b) {
  mat A = as_Mat(a);
  mat B = as_Mat(b);
  mat C = element_wise_multiply(A, B);
  return cpp4r::as_sexp(C);
}
