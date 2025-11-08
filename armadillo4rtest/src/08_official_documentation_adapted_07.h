[[cpp4r::register]] integers find_nan1_(const int& n) {
  mat A(n, n, fill::randu);
  A(0, 0) = datum::nan;
  uvec q = find_nan(A);
  return as_integers(q);
}

[[cpp4r::register]] integers find_unique1_(const int& n) {
  mat A(n, n, fill::randu);
  A(0, 0) = A(1, 1);
  uvec q = find_unique(A);
  return as_integers(q);
}

[[cpp4r::register]] list flip1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = fliplr(A);
  mat C = flipud(A);

  writable::list res(3);
  res[0] = as_doubles_matrix(A);
  res[1] = as_doubles_matrix(B);
  res[2] = as_doubles_matrix(C);

  return res;
}

[[cpp4r::register]] list imag1_(const int& n) {
  cx_mat X(n, n, fill::randu);
  mat Y = imag(X);
  mat Z = real(X);

  writable::list res(2);
  res[0] = as_doubles_matrix(Y);
  res[1] = as_doubles_matrix(Z);

  return res;
}

[[cpp4r::register]] list ind2sub1_(const int& n) {
  mat M(n, n, fill::randu);

  uvec s = ind2sub(size(M), n);

  uvec indices = find(M > 0.5);
  umat t = ind2sub(size(M), indices);

  cube Q(2, 3, 4);

  uvec u = ind2sub(size(Q), 8);

  writable::list res(3);
  res[0] = as_integers(s);
  res[1] = as_integers_matrix(t);
  res[2] = as_integers(u);

  return res;
}

[[cpp4r::register]] doubles index_min1_(const int& n) {
  mat M(n, n + 1, fill::randu);

  urowvec ii = index_max(M);
  ucolvec jj = index_max(M, 1);

  // max values in col 1 and row n
  return writable::doubles({M(ii(0), 0), M(n - 1, jj(n - 1))});
}

[[cpp4r::register]] doubles_matrix<> inplace_trans1_(const int& n) {
  mat X(n, n, fill::randu);
  inplace_trans(X);
  return as_doubles_matrix(X);
}

[[cpp4r::register]] complexes_matrix<> inplace_strans1_(const int& n) {
  cx_mat X(n, n, fill::randu);
  inplace_strans(X);
  return as_complexes_matrix(X);
}

[[cpp4r::register]] integers intersect1_(const int& n) {
  ivec A = regspace<ivec>(n, 1);      // n, ..., 1
  ivec B = regspace<ivec>(2, n + 1);  // 2, ..., n + 1

  ivec C = intersect(A, B);  // 2, ..., n

  return as_integers(C);
}

[[cpp4r::register]] list join_rows1_(const int& n) {
  mat A(n, 1, fill::randu);
  mat B(n, 1, fill::randu);
  mat C(n, 1, fill::randu);

  mat D = join_rows(A, B, C);
  mat E = join_cols(A, B, C);

  return writable::list({as_doubles_matrix(A), as_doubles_matrix(B), as_doubles_matrix(C),
                         as_doubles_matrix(D), as_doubles_matrix(E)});
}

[[cpp4r::register]] list join_cubes1_(const int& n) {
  cube C(n, n + 1, 3, fill::randu);
  cube D(n, n + 1, 4, fill::randu);

  cube E = join_slices(C, D);

  size_t m = C.n_slices + D.n_slices;

  writable::list res(m);

  for (size_t i = 0; i < m; ++i) {
    res[i] = as_doubles_matrix(E.slice(i));
  }

  return res;
}

[[cpp4r::register]] doubles_matrix<> kron1_(const int& n) {
  mat A(n, n + 1, fill::randu);
  mat B(n + 1, n, fill::randu);

  mat K = kron(A, B);

  return as_doubles_matrix(K);
}

[[cpp4r::register]] list log_det1_(const int& n) {
  mat A(n, n, fill::randu);

  cx_double res1 = log_det(A);  // form 1

  cpp4r::writable::list res2;
  res2.push_back(writable::doubles({std::real(res1)}));
  res2.push_back(writable::doubles({std::imag(res1)}));

  double val;
  double sign;
  bool ok = log_det(val, sign, A);  // form 2

  writable::list res3(3);
  res3[0] = doubles({val});
  res3[1] = doubles({sign});
  res3[2] = logicals({ok});

  writable::list res(2);
  res[0] = res2;
  res[1] = res3;

  return res;
}

[[cpp4r::register]] list log_det_sympd1_(const int& n) {
  mat A(n, n, fill::randu);
  A = A * A.t();  // make A symmetric positive definite

  double val = log_det_sympd(A);  // form 1

  double val2;
  bool ok = log_det_sympd(val2, A);  // form 2

  writable::list res(2);
  res[0] = doubles({val});

  writable::list res2(2);
  res2[0] = doubles({val2});
  res2[1] = logicals({ok});
  res[1] = res2;

  return res;
}

[[cpp4r::register]] complexes_matrix<> logmat1_(const int& n) {
  mat A(n, n, fill::randu);
  cx_mat B = logmat(A);
  return as_complexes_matrix(B);
}

[[cpp4r::register]] list logmat_sympd1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = A * A.t();  // make symmetric matrix

  mat C = logmat_sympd(B);

  writable::list res(2);

  res[0] = as_doubles_matrix(C);

  mat D;
  bool ok = logmat_sympd(D, B);

  writable::list res2(2);
  res2[0] = as_doubles_matrix(D);
  res2[1] = logicals({ok});

  res[1] = res2;

  return res;
}

[[cpp4r::register]] list max1_(const int& n) {
  mat M(n, n, fill::randu);

  rowvec a = max(M);
  rowvec b = max(M, 0);
  colvec c = max(M, 1);

  // element-wise maximum
  mat X(n, n, fill::randu);
  mat Y(n, n, fill::randu);
  mat Z = arma::max(X, Y);  // use arma:: prefix to distinguish from std::max()

  writable::list res(4);
  res[0] = as_doubles(a.t());
  res[1] = as_doubles(b.t());
  res[2] = as_doubles(c);
  res[3] = as_doubles_matrix(Z);

  return res;
}

[[cpp4r::register]] doubles nonzeros1_(const int& n) {
  mat A(n, n, fill::randu);
  A.elem(find(A < 0.5)).zeros();  // set elements less than 0.5 to zero
  vec B = nonzeros(A);
  return as_doubles(B);
}

[[cpp4r::register]] doubles norm1_(const int& n) {
  vec A(n, fill::randu);

  writable::doubles res(
      {norm(A, 1), norm(A, 2), norm(A, "inf"), norm(A, "-inf"), norm(A, "fro")});
  res.attr("names") =
      strings({"norm_1", "norm_2", "norm_inf", "norm_minus_inf", "norm_fro"});

  return res;
}

[[cpp4r::register]] doubles norm2est1_(const int& n) {
  mat A(n, n, fill::randu);
  return doubles({norm2est(A)});
}
