// OLS

// Example 1: vec to doubles()

[[cpp4r::register]] doubles ols_traditional_(const doubles_matrix<>& x,
                                             const doubles& y) {
  mat X = as_Mat(x);
  vec Y = as_Col(y);
  vec result = ols_fit(X, Y);
  return as_doubles(result);
}

// Example 2: vec to doubles using as_sexp()

[[cpp4r::register]] doubles ols_simplified_(const doubles_matrix<>& x, const doubles& y) {
  mat X = as_mat(x);
  vec Y = as_Col(y);
  return cpp4r::as_sexp(ols_fit(X, Y));
}

// Example 3: mat to doubles_matrix<> using as_sexp()

[[cpp4r::register]] doubles_matrix<> ols_simplified2_(const doubles_matrix<>& x,
                                                      const doubles& y) {
  mat X = as_mat(x);
  vec Y = as_Col(y);
  mat result = ols_fit(X, Y);
  return cpp4r::as_sexp(result);
}

// Example 4: vec to doubles using as_sexp()

[[cpp4r::register]] doubles ols_simplified3_(const doubles_matrix<>& x,
                                             const doubles& y) {
  mat X = as_mat(x);
  vec Y = as_Col(y);
  vec result = ols_fit(X, Y);
  return cpp4r::as_sexp(result);
}

// Example 4: vec to doubles using as_sexp()

[[cpp4r::register]] doubles ols_simplified4_(const doubles_matrix<>& x,
                                             const doubles& y) {
  return cpp4r::as_sexp(ols_fit(as_mat(x), as_col(y)));
}

// Example 5: vec to doubles using as_sexp()

[[cpp4r::register]] doubles_matrix<> ols_simplified5_(const doubles_matrix<>& x,
                                             const doubles& y) {
  return cpp4r::as_sexp(ols_fit(as_mat(x), as_col(y)));
}

// Matrix operations

// Example 1: mat to doubles_matrix<> using as_sexp()

[[cpp4r::register]] doubles_matrix<> matrix_add_(const doubles_matrix<>& a,
                                                 const doubles_matrix<>& b) {
  Mat<double> A = as_Mat(a);
  mat B = as_mat(b);
  mat C = A + B;
  return cpp4r::as_sexp(C);
}

// Example 2: imat to integers_matrix<> using as_sexp()

[[cpp4r::register]] integers_matrix<> integer_transpose_(const integers_matrix<>& x) {
  imat X = as_imat(x);
  imat Y = X.t();
  return cpp4r::as_sexp(Y);
}

// Example 3: umat to integers_matrix<> using as_umat

[[cpp4r::register]] integers_matrix<> uvec_example_(const integers_matrix<>& x) {
  umat X = as_umat(x);
  umat Y = X + 1;
  return cpp4r::as_sexp(Y);
}

// Example 4: fmat to doubles_matrix<> using as_sexp()

[[cpp4r::register]] doubles_matrix<> fmat_example_(const doubles_matrix<>& x) {
  fmat X = as_fmat(x);
  fmat Y = X * 2.0f;
  mat result = arma::conv_to<mat>::from(Y);
  return cpp4r::as_sexp(result);
}
