[[cpp4r::register]] list conv2_(const doubles_matrix<>& x, const doubles_matrix<>& y) {
  mat a = as_mat(x);
  mat b = as_mat(y);

  mat c = conv2(a, b);
  mat d = conv2(a, b, "same");

  writable::list out(2);
  out[0] = as_doubles_matrix(c);
  out[1] = as_doubles_matrix(d);

  return out;
}

[[cpp4r::register]] doubles interp1_(const int& n) {
  vec x = linspace<vec>(0, 3, n);
  vec y = square(x);

  vec xx = linspace<vec>(0, 3, 2 * n);
  vec yy;

  interp1(x, y, xx, yy);             // use linear interpolation by default
  interp1(x, y, xx, yy, "*linear");  // faster than "linear"
  interp1(x, y, xx, yy, "nearest");

  return as_doubles(yy);
}

[[cpp4r::register]] doubles_matrix<> interp2_(const int& n) {
  mat Z(n, n, fill::randu);

  vec X = regspace(1, Z.n_cols);  // X = horizontal spacing
  vec Y = regspace(1, Z.n_rows);  // Y = vertical spacing

  vec XI = regspace(X.min(), 1.0 / 2.0, X.max());  // magnify by approx 2
  vec YI = regspace(Y.min(), 1.0 / 3.0, Y.max());  // magnify by approx 3

  mat ZI;

  interp2(X, Y, Z, XI, YI, ZI);  // use linear interpolation by default

  return as_doubles_matrix(ZI);
}

[[cpp4r::register]] list fft1_(const doubles& x) {
  vec a = as_Col(x);

  cx_vec b = fft(a);
  cx_vec c = ifft(b);

  writable::list out(2);
  writable::list out2(2);
  writable::list out3(2);

  out2[0] = as_doubles(real(b));
  out2[1] = as_doubles(imag(b));

  out3[0] = as_doubles(real(c));
  out3[1] = as_doubles(imag(c));

  out[0] = out2;
  out[1] = out3;

  return out;
}

[[cpp4r::register]] list fft2_(const doubles_matrix<>& x) {
  mat a = as_mat(x);

  cx_mat b = fft2(a);
  cx_mat c = ifft2(b);

  writable::list out(2);
  writable::list out2(2);
  writable::list out3(2);

  mat b_real = real(b);
  mat b_imag = imag(b);

  mat c_real = real(c);
  mat c_imag = imag(c);

  out2[0] = as_doubles_matrix(b_real);
  out2[1] = as_doubles_matrix(b_imag);

  out3[0] = as_doubles_matrix(c_real);
  out3[1] = as_doubles_matrix(c_imag);

  out[0] = out2;
  out[1] = out3;

  return out;
}

[[cpp4r::register]] doubles polyfit1_(const int& n, const int& m) {
  vec x = linspace<vec>(0, 1, n);
  vec y = 2 * pow(x, 2) + 2 * x + ones<vec>(n);

  vec p = polyfit(x, y, m);

  return as_doubles(p);
}

[[cpp4r::register]] doubles polyval1_(const int& n, const int& m) {
  vec x = linspace<vec>(0, 1, n);
  vec y = 2 * pow(x, 2) + 2 * x + ones<vec>(n);

  vec p = polyfit(x, y, m);
  vec q = polyval(p, x);

  return as_doubles(q);
}

[[cpp4r::register]] list chol1_(const doubles_matrix<>& x, const char* layout,
                                const char* output) {
  mat X = as_mat(x);

  mat Y = X.t() * X;

  mat R;
  umat P;

  writable::list out(2);
  bool ok = chol(R, P, Y, layout, output);
  out[0] = logicals({ok});
  out[1] = as_doubles_matrix(R);

  return out;
}

[[cpp4r::register]] list eig_sym1_(const doubles_matrix<>& x, const char* method) {
  mat X = as_mat(x);

  vec eigval;
  mat eigvec;

  bool ok = eig_sym(eigval, eigvec, X, method);

  writable::list out(3);
  out[0] = logicals({ok});
  out[1] = as_doubles(eigval);
  out[2] = as_doubles_matrix(eigvec);

  return out;
}

[[cpp4r::register]] list eig_gen1_(const doubles_matrix<>& x, const char* balance) {
  mat X = as_mat(x);

  cx_vec eigval;
  cx_mat eigvec;

  bool ok = eig_gen(eigval, eigvec, X, balance);

  writable::list out(3);
  out[0] = logicals({ok});
  out[1] = as_complexes(eigval);
  out[2] = as_complexes_matrix(eigvec);

  return out;
}

[[cpp4r::register]] list eig_pair1_(const doubles_matrix<>& a,
                                    const doubles_matrix<>& b) {
  mat A = as_mat(a);
  mat B = as_mat(b);

  cx_vec eigval;
  cx_mat eigvec;

  bool ok = eig_pair(eigval, eigvec, A, B);

  writable::list out(3);
  out[0] = logicals({ok});
  out[1] = as_complexes(eigval);
  out[2] = as_complexes_matrix(eigvec);

  return out;
}

[[cpp4r::register]] list hess1_(const doubles_matrix<>& x) {
  mat X = as_mat(x);

  mat H;
  bool ok = hess(H, X);

  writable::list out(2);
  out[0] = logicals({ok});
  out[1] = as_doubles_matrix(H);

  return out;
}

[[cpp4r::register]] list inv1_(const doubles_matrix<>& a) {
  mat A = as_mat(a);

  mat B;
  bool ok = inv(B, A, inv_opts::allow_approx);

  writable::list out(2);
  out[0] = logicals({ok});
  out[1] = as_doubles_matrix(B);

  return out;
}

[[cpp4r::register]] list inv_sympd1_(const doubles_matrix<>& a) {
  mat A = as_mat(a);

  mat B;
  bool ok = inv_sympd(B, A, inv_opts::allow_approx);

  writable::list out(2);
  out[0] = logicals({ok});
  out[1] = as_doubles_matrix(B);

  return out;
}

[[cpp4r::register]] list lu1_(const doubles_matrix<>& x) {
  mat X = as_mat(x);

  mat L, U, P;

  bool ok = lu(L, U, P, X);

  writable::list out(4);
  out[0] = logicals({ok});
  out[1] = as_doubles_matrix(L);
  out[2] = as_doubles_matrix(U);
  out[3] = as_doubles_matrix(P);

  return out;
}

[[cpp4r::register]] list null1_(const doubles_matrix<>& a) {
  mat A = as_mat(a);

  A.row(0).zeros();  // make the first row zero
  A.col(0).zeros();  // make the first column zero

  mat B;
  bool ok = null(B, A);

  writable::list out(2);
  out[0] = logicals({ok});
  out[1] = as_doubles_matrix(B);

  return out;
}

[[cpp4r::register]] list orth1_(const doubles_matrix<>& a) {
  mat A = as_mat(a);

  mat B;
  bool ok = orth(B, A);

  writable::list out(2);
  out[0] = logicals({ok});
  out[1] = as_doubles_matrix(B);

  return out;
}

[[cpp4r::register]] list pinv1_(const doubles_matrix<>& a) {
  mat A = as_mat(a);

  mat B = pinv(A);

  writable::list out(1);
  out[0] = as_doubles_matrix(B);

  return out;
}

[[cpp4r::register]] list qr1_(const doubles_matrix<>& x) {
  mat X = as_mat(x);

  mat Q, R;
  // umat P;

  // bool ok = qr(Q, R, P, X, "matrix");
  bool ok = qr(Q, R, X);

  // writable::list out(4);
  writable::list out(3);
  out[0] = logicals({ok});
  out[1] = as_doubles_matrix(Q);
  out[2] = as_doubles_matrix(R);
  // out[3] = as_integers_matrix(P);

  return out;
}

[[cpp4r::register]] list qr_econ1_(const doubles_matrix<>& x) {
  mat X = as_mat(x);

  mat Q, R;

  bool ok = qr_econ(Q, R, X);

  writable::list out(3);
  out[0] = logicals({ok});
  out[1] = as_doubles_matrix(Q);
  out[2] = as_doubles_matrix(R);

  return out;
}

[[cpp4r::register]] list qz1_(const doubles_matrix<>& a, const doubles_matrix<>& b,
                              const char* select) {
  mat A = as_mat(a);
  mat B = as_mat(b);

  mat AA, BB, Q, Z;

  bool ok = qz(AA, BB, Q, Z, A, B, select);

  writable::list out(5);
  out[0] = logicals({ok});
  out[1] = as_doubles_matrix(AA);
  out[2] = as_doubles_matrix(BB);
  out[3] = as_doubles_matrix(Q);
  out[4] = as_doubles_matrix(Z);

  return out;
}

[[cpp4r::register]] list schur1_(const doubles_matrix<>& x) {
  mat X = as_mat(x);

  mat U, S;

  bool ok = schur(U, S, X);

  writable::list out(3);
  out[0] = logicals({ok});
  out[1] = as_doubles_matrix(U);
  out[2] = as_doubles_matrix(S);

  return out;
}

[[cpp4r::register]] doubles_matrix<> solve1_(const doubles_matrix<>& a,
                                             const doubles_matrix<>& b) {
  mat A = as_mat(a);
  mat B = as_mat(b);

  mat X = solve(A, B);

  return as_doubles_matrix(X);
}

[[cpp4r::register]] list svd1_(const doubles_matrix<>& x) {
  mat X = as_mat(x);

  mat U;
  vec s;
  mat V;

  bool ok = svd(U, s, V, X);

  writable::list out(4);
  out[0] = logicals({ok});
  out[1] = as_doubles_matrix(U);
  out[2] = as_doubles(s);
  out[3] = as_doubles_matrix(V);

  return out;
}

[[cpp4r::register]] list svd_econ1_(const doubles_matrix<>& x) {
  mat X = as_mat(x);

  mat U;
  vec s;
  mat V;

  svd_econ(U, s, V, X);

  writable::list out(3);
  out[0] = as_doubles_matrix(U);
  out[1] = as_doubles(s);
  out[2] = as_doubles_matrix(V);

  return out;
}

[[cpp4r::register]] doubles_matrix<> syl1_(const doubles_matrix<>& a,
                                           const doubles_matrix<>& b,
                                           const doubles_matrix<>& c) {
  mat A = as_mat(a);
  mat B = as_mat(b);
  mat C = as_mat(c);

  mat X = sylvester(A, B, C);

  return as_doubles_matrix(X);
}

#ifndef ARMADILLO4R_NO_SPARSE

[[cpp4r::register]] list eig_sym2_(const doubles_matrix<>& x, const char* method,
                                   const int& k) {
  sp_mat X = as_SpMat(x);

  sp_mat Y = X.t() * X;

  vec eigval;
  mat eigvec;

  eigs_opts opts;
  opts.maxiter = 10000;
  bool ok = eigs_sym(eigval, eigvec, Y, k, method, opts);

  writable::list out(3);
  out[0] = logicals({ok});
  out[1] = as_doubles(eigval);
  out[2] = as_doubles_matrix(eigvec);

  return out;
}

[[cpp4r::register]] list eig_gen2_(const doubles_matrix<>& x, const char* method,
                                   const int& k) {
  sp_mat X = as_SpMat(x);

  cx_vec eigval;
  cx_mat eigvec;

  eigs_opts opts;
  opts.maxiter = 10000;

  bool ok = eigs_gen(eigval, eigvec, X, k, method, opts);

  writable::list out(3);
  out[0] = logicals({ok});
  out[1] = as_complexes(eigval);
  out[2] = as_complexes_matrix(eigvec);

  return out;
}

[[cpp4r::register]] list svds1_(const doubles_matrix<>& x, const int& k) {
  sp_mat X = as_SpMat(x);

  // convert all values below 0.1 to zero
  X.transform([](double val) { return (std::abs(val) < 0.1) ? 0 : val; });

  mat U;
  vec s;
  mat V;

  bool ok = svds(U, s, V, X, k);

  writable::list out(4);
  out[0] = logicals({ok});
  out[1] = as_doubles(s);
  out[2] = as_doubles_matrix(U);
  out[3] = as_doubles_matrix(V);

  return out;
}

[[cpp4r::register]] doubles spsolve1_(const doubles_matrix<>& a, const doubles& b,
                                      const char* method) {
  sp_mat A = as_SpMat(a);
  vec B = as_Col(b);

  vec X = spsolve(A, B, method);

  return as_doubles(X);
}

#endif  // ARMADILLO4R_NO_SPARSE
