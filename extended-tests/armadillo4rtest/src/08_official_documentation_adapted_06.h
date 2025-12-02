[[cpp4r::register]] doubles_matrix<> clamp2_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = clamp(A, 0.2, 0.8);
  mat C = clamp(A, A.min(), 0.8);
  mat D = clamp(A, 0.2, A.max());

  mat res = B + C + D;

  return as_doubles_matrix(res);
}

[[cpp4r::register]] double cond1_(const int& n) {
  mat A(n, n);
  A.eye();  // the identity matrix has a condition number of 1

  double cond_num = cond(A);

  return cond_num;
}

[[cpp4r::register]] complexes_matrix<> conj1_(const int& n) {
  cx_mat X(n, n, fill::randu);
  cx_mat Y = conj(X);
  return as_complexes_matrix(Y);
}

[[cpp4r::register]] doubles conv_to1_(const int& n) {
  mat A(n, n, fill::randu);
  fmat B = conv_to<fmat>::from(A);

  std::vector<double> x(B.n_elem);

  int i, N = static_cast<int>(B.n_elem);
  for (i = 0; i < N; ++i) {
    x[i] = B(i);
  }

  colvec y = conv_to<colvec>::from(x);
  std::vector<double> z = conv_to<std::vector<double>>::from(y);

  return as_doubles(z);
}

[[cpp4r::register]] doubles cross1_(const int& n) {
  vec A(n, fill::randu);
  vec B(n, fill::randu);

  vec C = cross(A, B);

  return as_doubles(C);
}

[[cpp4r::register]] doubles cumsum1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = cumsum(A);
  mat C = cumsum(A, 1);

  vec x(n, fill::randu);
  vec y = cumsum(x);

  writable::doubles res(3);
  res[0] = accu(B);
  res[1] = accu(C);
  res[2] = accu(y);

  return res;
}

[[cpp4r::register]] doubles cumprod1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = cumprod(A);
  mat C = cumprod(A, 1);

  vec x(n, fill::randu);
  vec y = cumprod(x);

  writable::doubles res(3);
  res[0] = accu(B);
  res[1] = accu(C);
  res[2] = accu(y);

  return res;
}

[[cpp4r::register]] doubles det1_(const int& n) {
  mat A(n, n, fill::randu);
  double val1 = det(A);

  double val2;
  mat B(n, n, fill::randu);
  bool success2 = det(val2, B);

  return writable::doubles({val1, val2, static_cast<double>(success2)});
}

[[cpp4r::register]] doubles_matrix<> diagmat1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = diagmat(A);
  mat C = diagmat(A, 1);

  vec v(n, fill::randu);
  mat D = diagmat(v);     // NxN diagonal matrix
  mat E = diagmat(v, 1);  // (N+1)x(N+1) diagonal matrix

  mat res = B + C + D;
  res += E.submat(0, 0, n - 1, n - 1);  // the result is an upper triangular
                                        // matrix

  return as_doubles_matrix(res);
}

[[cpp4r::register]] doubles diagvec1_(const int& n) {
  mat A(n, n, fill::randu);
  vec B = diagvec(A, -1);
  vec C = diagvec(A, 1);

  vec res = B + C;

  return as_doubles(res);
}

[[cpp4r::register]] doubles_matrix<> diags1_(const int& n) {
  mat V(n, n, fill::randu);
  ivec D = {0, -1};
  mat X = diags(V, D, n, n);  // lower triangular matrix
  return as_doubles_matrix(X);
}

[[cpp4r::register]] doubles_matrix<> spdiags1_(const int& n) {
  mat V(n, n, fill::randu);
  ivec D = {0, -1};
  sp_mat X = spdiags(V, D, n, n);  // lower triangular matrix
  return as_doubles_matrix(X);
}

[[cpp4r::register]] doubles_matrix<> diff1_(const int& n) {
  vec a = randu<vec>(n);
  vec b = diff(a);

  mat res(n, 2, fill::zeros);

  res.col(0) = a;

  for (int i = 1; i < n; ++i) {
    res(i, 1) = b(i - 1);
  }

  return as_doubles_matrix(res);
}

[[cpp4r::register]] doubles dot1_(const int& n) {
  vec A(n, fill::randu);
  vec B(n, fill::randu);
  return writable::doubles({dot(A, B), cdot(A, B), norm_dot(A, B)});
}

[[cpp4r::register]] doubles_matrix<> eps1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = eps(A);
  return as_doubles_matrix(B);
}

[[cpp4r::register]] doubles_matrix<> expmat1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = expmat(A);
  return as_doubles_matrix(B);
}

[[cpp4r::register]] doubles_matrix<> expmat_sym1_(const int& n) {
  mat A(n, n, fill::randu);
  A = A + A.t();  // make A symmetric
  mat B = expmat_sym(A);
  return as_doubles_matrix(B);
}

[[cpp4r::register]] list find1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B(n, n, fill::randu);

  uvec q1 = find(A > B);
  uvec q2 = find(A > 0.5);
  uvec q3 = find(A > 0.5, 3, "last");

  // change elements of A greater than 0.5 to 1
  A.elem(find(A > 0.5)).ones();

  writable::list res(3);
  res[0] = as_integers(q1);
  res[1] = as_integers(q2);
  res[2] = as_integers(q3);

  return res;
}

[[cpp4r::register]] integers find_finite1_(const int& n) {
  mat A(n, n, fill::randu);
  uvec q = find_finite(A);
  return as_integers(q);
}

[[cpp4r::register]] integers find_nonfinite1_(const int& n) {
  mat A(n, n, fill::randu);
  A(0, 0) = datum::inf;
  uvec q = find_nonfinite(A);
  return as_integers(q);
}
