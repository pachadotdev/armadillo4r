/* roxygen
@title conv2() 2D convolution demo (full and same modes)
@param x numeric matrix (kernel)
@param y numeric matrix (signal)
@return list with full-size and same-size 2D convolution results
@export
*/
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

/* roxygen
@title interp1() 1D interpolation demo (linear and nearest-neighbor)
@param n integer scalar; number of data points
@return numeric vector (2N): interpolated values at finer grid
@export
*/
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

/* roxygen
@title interp2() 2D interpolation demo
@param n integer scalar; grid dimension
@return numeric matrix: bilinearly interpolated surface on a finer grid
@export
*/
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

/* roxygen
@title fft() and ifft() 1D fast Fourier transform demo
@param x numeric vector
@return list with FFT result (real/imag) and inverse FFT result (real/imag)
@export
*/
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

/* roxygen
@title fft2() and ifft2() 2D fast Fourier transform demo
@param x numeric matrix
@return list with 2D FFT result (real/imag) and inverse 2D FFT result
  (real/imag)
@export
*/
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

/* roxygen
@title polyfit() polynomial curve fitting demo
@param n integer scalar; number of data points
@param m integer scalar; polynomial degree
@return numeric vector (M+1): fitted polynomial coefficients
@export
*/
[[cpp4r::register]] doubles polyfit1_(const int& n, const int& m) {
  vec x = linspace<vec>(0, 1, n);
  vec y = 2 * pow(x, 2) + 2 * x + ones<vec>(n);

  vec p = polyfit(x, y, m);

  return as_doubles(p);
}

/* roxygen
@title polyval() polynomial evaluation demo
@param n integer scalar; number of evaluation points
@param m integer scalar; polynomial degree
@return numeric vector (N): polynomial values evaluated at N points
@export
*/
[[cpp4r::register]] doubles polyval1_(const int& n, const int& m) {
  vec x = linspace<vec>(0, 1, n);
  vec y = 2 * pow(x, 2) + 2 * x + ones<vec>(n);

  vec p = polyfit(x, y, m);
  vec q = polyval(p, x);

  return as_doubles(q);
}

/* roxygen
@title chol() Cholesky decomposition with pivoting demo
@param x numeric positive semi-definite matrix (N*N)
@param layout string scalar; `"upper"` or `"lower"`
@param output string scalar; `"matrix"` for pivot matrix, `"vector"` for
  pivot vector
@return list with success flag and triangular factor matrix
@export
*/
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

/* roxygen
@title eig_sym() symmetric eigendecomposition demo (two forms)
@param x symmetric numeric matrix (N*N)
@param method string scalar; `"dc"` (divide-and-conquer) or `"std"`
@return list with success flag, eigenvalue vector, and eigenvector matrix
@export
*/
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

/* roxygen
@title eig_gen() general eigendecomposition demo with optional balancing
@param x numeric matrix (N*N)
@param balance string scalar; `"balance"` or `"nobalance"`
@return list with success flag, complex eigenvalue vector, and complex
  eigenvector matrix
@export
*/
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

/* roxygen
@title eig_pair() generalized eigendecomposition (A*x = lambda*B*x) demo
@param a numeric matrix (N*N)
@param b numeric matrix (N*N)
@return list with success flag, complex eigenvalue vector, and complex
  eigenvector matrix
@export
*/
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

/* roxygen
@title hess() Hessenberg decomposition demo
@param x numeric matrix (N*N)
@return list with success flag and upper Hessenberg matrix
@export
*/
[[cpp4r::register]] list hess1_(const doubles_matrix<>& x) {
  mat X = as_mat(x);

  mat H;
  bool ok = hess(H, X);

  writable::list out(2);
  out[0] = logicals({ok});
  out[1] = as_doubles_matrix(H);

  return out;
}

/* roxygen
@title inv() matrix inversion with approximate fallback demo
@param a numeric square matrix (N*N)
@return list with success flag and inverse matrix
@export
*/
[[cpp4r::register]] list inv1_(const doubles_matrix<>& a) {
  mat A = as_mat(a);

  mat B;
  bool ok = inv(B, A, inv_opts::allow_approx);

  writable::list out(2);
  out[0] = logicals({ok});
  out[1] = as_doubles_matrix(B);

  return out;
}

/* roxygen
@title inv_sympd() symmetric positive definite matrix inversion demo
@param a numeric symmetric positive definite matrix (N*N)
@return list with success flag and inverse matrix
@export
*/
[[cpp4r::register]] list inv_sympd1_(const doubles_matrix<>& a) {
  mat A = as_mat(a);

  mat B;
  bool ok = inv_sympd(B, A, inv_opts::allow_approx);

  writable::list out(2);
  out[0] = logicals({ok});
  out[1] = as_doubles_matrix(B);

  return out;
}

/* roxygen
@title lu() LU decomposition with pivoting demo
@param x numeric matrix (N*N)
@return list with success flag and L, U, P matrices
@export
*/
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

/* roxygen
@title null() null space computation demo
@param a numeric matrix (rows and first column zeroed)
@return list with success flag and null space matrix
@export
*/
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

/* roxygen
@title orth() orthonormal basis computation demo
@param a numeric matrix
@return list with success flag and orthonormal basis matrix
@export
*/
[[cpp4r::register]] list orth1_(const doubles_matrix<>& a) {
  mat A = as_mat(a);

  mat B;
  bool ok = orth(B, A);

  writable::list out(2);
  out[0] = logicals({ok});
  out[1] = as_doubles_matrix(B);

  return out;
}

/* roxygen
@title pinv() Moore-Penrose pseudoinverse demo
@param a numeric matrix
@return list with pseudoinverse matrix
@export
*/
[[cpp4r::register]] list pinv1_(const doubles_matrix<>& a) {
  mat A = as_mat(a);

  mat B = pinv(A);

  writable::list out(1);
  out[0] = as_doubles_matrix(B);

  return out;
}

/* roxygen
@title qr() QR decomposition demo
@param x numeric matrix
@return list with success flag, Q matrix, and R matrix
@export
*/
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

/* roxygen
@title qr_econ() economic QR decomposition demo
@param x numeric matrix (N*P, N >= P)
@return list with success flag, thin Q matrix (N*P), and R matrix (P*P)
@export
*/
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

/* roxygen
@title qz() generalized Schur (QZ) decomposition demo
@param a numeric matrix (N*N)
@param b numeric matrix (N*N)
@param select string scalar; eigenvalue selection: `"lhp"`, `"rhp"`, `"iuc"`,
  `"ouc"`, or `"none"`
@return list with success flag and AA, BB, Q, Z matrices
@export
*/
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

/* roxygen
@title schur() Schur decomposition demo
@param x numeric matrix (N*N)
@return list with success flag, unitary matrix U, and quasi-upper-triangular
  matrix S
@export
*/
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

/* roxygen
@title solve() linear system solution demo
@param a numeric matrix (N*N)
@param b numeric matrix (N*M)
@return numeric matrix (N*M): solution X to A*X = B
@export
*/
[[cpp4r::register]] doubles_matrix<> solve1_(const doubles_matrix<>& a,
                                             const doubles_matrix<>& b) {
  mat A = as_mat(a);
  mat B = as_mat(b);

  mat X = solve(A, B);

  return as_doubles_matrix(X);
}

/* roxygen
@title svd() singular value decomposition demo
@param x numeric matrix (M*N)
@return list with success flag, U matrix, singular value vector, and V matrix
@export
*/
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

/* roxygen
@title svd_econ() economic SVD demo
@param x numeric matrix (M*N)
@return list with thin U matrix, singular value vector, and thin V matrix
@export
*/
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

/* roxygen
@title sylvester() Sylvester equation solver (A*X + X*B = C) demo
@param a numeric matrix (N*N)
@param b numeric matrix (N*N)
@param c numeric matrix (N*N)
@return numeric matrix (N*N): solution X
@export
*/
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

/* roxygen
@title eigs_sym() sparse symmetric eigendecomposition demo
@param x numeric matrix (used to form a sparse sym-pos-def matrix)
@param method string scalar; `"lm"` (largest magnitude) or `"sm"`
@param k integer scalar; number of eigenvalues to compute
@return list with success flag, eigenvalue vector, and eigenvector matrix
@export
*/
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

/* roxygen
@title eigs_gen() sparse general eigendecomposition demo
@param x numeric matrix (used as a sparse matrix)
@param method string scalar; `"lm"` (largest magnitude) or `"sm"`
@param k integer scalar; number of eigenvalues to compute
@return list with success flag, complex eigenvalue vector, and complex
  eigenvector matrix
@export
*/
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

/* roxygen
@title svds() sparse singular value decomposition demo
@param x numeric matrix (used as a sparse matrix)
@param k integer scalar; number of singular values to compute
@return list with success flag, singular value vector, U matrix, and V matrix
@export
*/
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

/* roxygen
@title spsolve() sparse linear system solver demo
@param a numeric matrix (used as a sparse matrix N*N)
@param b numeric vector (N)
@param method string scalar; `"superlu"` or `"lapack"`
@return numeric vector (N): solution X to A*X = B
@export
*/
[[cpp4r::register]] doubles spsolve1_(const doubles_matrix<>& a, const doubles& b,
                                      const char* method) {
  sp_mat A = as_SpMat(a);
  vec B = as_Col(b);

  vec X = spsolve(A, B, method);

  return as_doubles(X);
}

#endif  // ARMADILLO4R_NO_SPARSE
