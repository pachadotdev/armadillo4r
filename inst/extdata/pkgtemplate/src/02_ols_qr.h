Mat<double> ols_qr_(const doubles_matrix<>& y, const doubles_matrix<>& x) {
  Mat<double> Y = as_Mat(y);  // Col<double> Y = as_Col(y); also works
  Mat<double> X = as_Mat(x);

  Mat<double> XtX = X.t() * X;  // X'X

  // numerically more stable via QR decomposition
  // Mat<double> XtX_inv = inv(XtX);          // (X'X)^(-1)

  mat Q, R;
  bool ok = qr_econ(Q, R, XtX);

  if (ok) {
    Mat<double> XtX_inv = inv(R) * Q.t();  // (X'X)^(-1) via QR
  } else {
    cpp4r::stop("QR decomposition failed in ols_qr_()");
  }

  Mat<double> beta = XtX_inv * X.t() * Y;  // (X'X)^(-1)(X'Y)

  return beta;
}

[[cpp4r::register]] doubles_matrix<> ols_qr_mat(const doubles_matrix<>& y,
                                                const doubles_matrix<>& x) {
  Mat<double> beta = ols_qr_(y, x);
  return as_doubles_matrix(beta);
}
