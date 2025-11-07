#include "00_main.h"

// Example 1: Traditional approach (still supported)
// User needs to manually convert types

vec ols_fit_traditional(const Mat<double>& X, const Col<double>& Y) {
  mat Q, R;
  qr_econ(Q, R, X);
  vec betas = solve(trimatu(R), Q.t() * Y);
  return betas;
}

[[cpp4r::register]] doubles ols_traditional_(const doubles_matrix<>& x,
                                             const doubles& y) {
  mat X = as_Mat(x);
  vec Y = as_Col(y);
  vec result = ols_fit_traditional(X, Y);
  return as_doubles(result);
}

// Example 2: Using as_arma() helper function
// Cleaner, explicit conversion at call site

vec ols_fit_helper(const Mat<double>& X, const Col<double>& Y) {
  mat Q, R;
  qr_econ(Q, R, X);
  vec betas = solve(trimatu(R), Q.t() * Y);
  return betas;
}

[[cpp4r::register]] doubles ols_helper_(const doubles_matrix<>& x,
                                        const doubles& y) {
  return cpp4r::as_sexp(ols_fit_helper(as_arma(x), as_arma(y)));
}

// Example 3: Using wrapper classes
// Most seamless - automatic conversion in function signature

vec ols_fit_wrapper(const armadillo4r::mat_wrapper& X,
                    const armadillo4r::vec_wrapper& Y) {
  mat Q, R;
  qr_econ(Q, R, X);
  vec betas = solve(trimatu(R), Q.t() * Y);
  return betas;
}

[[cpp4r::register]] doubles ols_wrapper_(const doubles_matrix<>& x,
                                         const doubles& y) {
  return cpp4r::as_sexp(ols_fit_wrapper(x, y));
}

// Example 4: Matrix operations with different types

[[cpp4r::register]] doubles_matrix<> matrix_add_helper_(
    const doubles_matrix<>& a, const doubles_matrix<>& b) {
  mat A = as_arma(a);
  mat B = as_arma(b);
  mat C = A + B;
  return cpp4r::as_sexp(C);
}

[[cpp4r::register]] doubles_matrix<> matrix_add_wrapper_(
    const doubles_matrix<>& a, const doubles_matrix<>& b) {
  armadillo4r::mat_wrapper A(a);
  armadillo4r::mat_wrapper B(b);
  mat C = A + B;
  return cpp4r::as_sexp(C);
}

// Example 5: Integer matrix conversion

[[cpp4r::register]] integers_matrix<> integer_transpose_(
    const integers_matrix<>& x) {
  imat X = as_arma(x);
  imat Y = X.t();
  return cpp4r::as_sexp(Y);
}

// Example 6: Complex matrix operations

[[cpp4r::register]] complexes_matrix<> complex_multiply_(
    const complexes_matrix<>& a, const complexes_matrix<>& b) {
  cx_mat A = as_arma(a);
  cx_mat B = as_arma(b);
  cx_mat C = A * B;
  return cpp4r::as_sexp(C);
}

// Example 7: Generic function that works with multiple types

template <typename T>
T element_wise_multiply(const T& A, const T& B) {
  return A % B;  // element-wise multiplication
}

[[cpp4r::register]] doubles_matrix<> generic_multiply_(
    const doubles_matrix<>& a, const doubles_matrix<>& b) {
  mat A = as_arma(a);
  mat B = as_arma(b);
  mat C = element_wise_multiply(A, B);
  return cpp4r::as_sexp(C);
}
