Mat<double> ols_(const doubles_matrix<>& y, const doubles_matrix<>& x) {
  Mat<double> Y = as_Mat(y);  // Col<double> Y = as_Col(y); also works
  Mat<double> X = as_Mat(x);

  Mat<double> XtX = X.t() * X;             // X'X
  Mat<double> XtX_inv = inv(XtX);          // (X'X)^(-1)
  Mat<double> beta = XtX_inv * X.t() * Y;  // (X'X)^(-1)(X'Y)

  return beta;
}

/* roxygen
@title OLS coefficients as a matrix
@param y response matrix (N*1)
@param x design matrix (N*P)
@return coefficient matrix (P*1)
@export
*/
[[cpp4r::register]] doubles_matrix<> ols_mat(const doubles_matrix<>& y,
                                             const doubles_matrix<>& x) {
  return as_doubles_matrix(ols_(y, x));
}

/* roxygen
@title OLS coefficients as a vector
@param y response matrix (N*1)
@param x design matrix (N*P)
@return coefficient vector (P)
@export
*/
[[cpp4r::register]] doubles ols_dbl(const doubles_matrix<>& y,
                                    const doubles_matrix<>& x) {
  return as_doubles(ols_(y, x));
}
