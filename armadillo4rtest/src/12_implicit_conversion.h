// Example 1: vec to doubles

[[cpp4r::register]] doubles ols_traditional_(const doubles_matrix<>& x,
                                             const doubles& y) {
  mat X = as_Mat(x);
  vec Y = as_Col(y);
  vec result = ols_fit(X, Y);
  return as_doubles(result);
}

// Example 2: vec to doubles using as_sexp

[[cpp4r::register]] doubles ols_simplified_(const doubles_matrix<>& x, const doubles& y) {
  mat X = as_mat(x);
  vec Y = as_Col(y);
  return cpp4r::as_sexp(ols_fit(X, Y));
}

// Example 3: mat to doubles_matrix<> using as_sexp

[[cpp4r::register]] doubles_matrix<> ols_simplified2_(const doubles_matrix<>& x,
                                                      const doubles& y) {
  mat X = as_mat(x);
  vec Y = as_Col(y);
  mat result = ols_fit(X, Y);
  return cpp4r::as_sexp(result);
}

// Example 4: vec to doubles using as_sexp

[[cpp4r::register]] doubles ols_simplified3_(const doubles_matrix<>& x,
                                             const doubles& y) {
  mat X = as_mat(x);
  vec Y = as_Col(y);
  vec result = ols_fit(X, Y);
  return cpp4r::as_sexp(result);
}

// Example 3: Matrix operations

[[cpp4r::register]] doubles_matrix<> matrix_add_(const doubles_matrix<>& a,
                                                 const doubles_matrix<>& b) {
  Mat<double> A = as_Mat(a);
  mat B = as_mat(b);
  mat C = A + B;
  return cpp4r::as_sexp(C);
}

// Example 4: Integer matrix operations using as_imat

[[cpp4r::register]] integers_matrix<> integer_transpose_(const integers_matrix<>& x) {
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

[[cpp4r::register]] complexes_matrix<> complex_multiply_(const complexes_matrix<>& a,
                                                         const complexes_matrix<>& b) {
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

[[cpp4r::register]] doubles_matrix<> generic_multiply_(const doubles_matrix<>& a,
                                                       const doubles_matrix<>& b) {
  mat A = as_Mat(a);
  mat B = as_Mat(b);
  mat C = element_wise_multiply(A, B);
  return cpp4r::as_sexp(C);
}

// Summary of cpp4r::as_sexp() behavior:
//
// INPUT TYPE           OUTPUT TYPE          NOTES
// -----------          -----------          -----
// arma::vec            doubles              Returns R vector
// arma::mat            doubles_matrix<>     Returns R matrix
// arma::ivec           integers             Returns R integer vector
// arma::imat           integers_matrix<>    Returns R integer matrix
// arma::uvec           integers             Returns R integer vector (converted)
// arma::umat           integers_matrix<>    Returns R integer matrix (converted)
// arma::rowvec         doubles_matrix<>     Returns R matrix (1 row x N cols)
//
// Key principle: The return type is determined by the INPUT Armadillo type,
// not by the C++ function's return type declaration.
//
// To return a vector as a matrix:
//   vec v = ...;
//   mat m = v;  // Convert vec to mat (single column)
//   return cpp4r::as_sexp(m);  // Returns doubles_matrix<>
//
// To return a single-column matrix as a vector:
//   mat m = ...;  // Single column matrix
//   vec v = m;    // Convert mat to vec
//   return cpp4r::as_sexp(v);  // Returns doubles
//
// Alternative: Use explicit conversion functions
//   return as_doubles(vec_or_mat);  // Always returns R vector
//   return as_doubles_matrix(vec_or_mat);  // Always returns R matrix

