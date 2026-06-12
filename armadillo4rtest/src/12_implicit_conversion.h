// OLS

// Example 1: vec to doubles()

/* roxygen
@title OLS via QR using explicit as_doubles() conversion
@param x design matrix (N*P)
@param y response vector (N)
@return numeric vector (P): OLS coefficient estimates
@export
*/
[[cpp4r::register]] doubles ols_traditional_(const doubles_matrix<>& x,
                                             const doubles& y) {
  mat X = as_Mat(x);
  vec Y = as_Col(y);
  return as_doubles(ols_fit(X, Y));
}

// Example 2: vec to doubles using as_sexp()

/* roxygen
@title OLS via QR using cpp4r::as_sexp() for vec-to-doubles conversion
@param x design matrix (N*P)
@param y response vector (N)
@return numeric vector (P): OLS coefficient estimates
@export
*/
[[cpp4r::register]] doubles ols_simplified_(const doubles_matrix<>& x, const doubles& y) {
  mat X = as_mat(x);
  vec Y = as_Col(y);
  return cpp4r::as_sexp(ols_fit(X, Y));
}

// Example 3: mat to doubles_matrix<> using as_sexp()

/* roxygen
@title OLS via QR returning a matrix using cpp4r::as_sexp()
@param x design matrix (N*P)
@param y response vector (N)
@return numeric matrix (P*1): OLS coefficient estimates
@export
*/
[[cpp4r::register]] doubles_matrix<> ols_simplified2_(const doubles_matrix<>& x,
                                                      const doubles& y) {
  mat X = as_mat(x);
  vec Y = as_Col(y);
  return cpp4r::as_sexp(ols_fit(X, Y));
}

// Example 4: vec to doubles using as_sexp()

/* roxygen
@title OLS via QR using cpp4r::as_sexp() (form 3)
@param x design matrix (N*P)
@param y response vector (N)
@return numeric vector (P): OLS coefficient estimates
@export
*/
[[cpp4r::register]] doubles ols_simplified3_(const doubles_matrix<>& x,
                                             const doubles& y) {
  mat X = as_mat(x);
  vec Y = as_Col(y);
  return cpp4r::as_sexp(ols_fit(X, Y));
}

// Example 4: vec to doubles using as_sexp()

/* roxygen
@title One-liner OLS using cpp4r::as_sexp() and as_col()
@param x design matrix (N*P)
@param y response vector (N)
@return numeric vector (P): OLS coefficient estimates
@export
*/
[[cpp4r::register]] doubles ols_simplified4_(const doubles_matrix<>& x,
                                             const doubles& y) {
  return cpp4r::as_sexp(ols_fit(as_mat(x), as_col(y)));
}

// Example 5: vec to doubles using as_sexp()

/* roxygen
@title One-liner OLS returning a matrix using cpp4r::as_sexp() and as_col()
@param x design matrix (N*P)
@param y response vector (N)
@return numeric matrix (P*1): OLS coefficient estimates
@export
*/
[[cpp4r::register]] doubles_matrix<> ols_simplified5_(const doubles_matrix<>& x,
                                                      const doubles& y) {
  return cpp4r::as_sexp(ols_fit(as_mat(x), as_col(y)));
}

// Matrix operations

// Example 1: mat to doubles_matrix<> using as_sexp()

/* roxygen
@title Matrix addition using cpp4r::as_sexp()
@param a numeric matrix
@param b numeric matrix
@return numeric matrix: element-wise sum of `a` and `b`
@export
*/
[[cpp4r::register]] doubles_matrix<> matrix_add_(const doubles_matrix<>& a,
                                                 const doubles_matrix<>& b) {
  Mat<double> A = as_Mat(a);
  mat B = as_mat(b);
  mat C = A + B;
  return cpp4r::as_sexp(C);
}

// Example 2: imat to integers_matrix<> using as_sexp()

/* roxygen
@title Integer matrix transpose using as_imat() and cpp4r::as_sexp()
@param x integer matrix
@return integer matrix: transpose of the input
@export
*/
[[cpp4r::register]] integers_matrix<> integer_transpose_(const integers_matrix<>& x) {
  imat X = as_imat(x);
  imat Y = X.t();
  return cpp4r::as_sexp(Y);
}

// Example 3: umat to integers_matrix<> using as_umat

/* roxygen
@title Unsigned integer matrix increment using as_umat() and cpp4r::as_sexp()
@param x integer matrix
@return integer matrix: input matrix with all elements incremented by 1
@export
*/
[[cpp4r::register]] integers_matrix<> uvec_example_(const integers_matrix<>& x) {
  umat X = as_umat(x);
  umat Y = X + 1;
  return cpp4r::as_sexp(Y);
}

// Example 4: fmat to doubles_matrix<> using as_sexp()

/* roxygen
@title Float matrix scaling using as_fmat() and cpp4r::as_sexp()
@param x numeric matrix
@return numeric matrix: input scaled by 2 (via single-precision arithmetic)
@export
*/
[[cpp4r::register]] doubles_matrix<> fmat_example_(const doubles_matrix<>& x) {
  fmat X = as_fmat(x);
  fmat Y = X * 2.0f;
  mat result = arma::conv_to<mat>::from(Y);
  return cpp4r::as_sexp(result);
}
