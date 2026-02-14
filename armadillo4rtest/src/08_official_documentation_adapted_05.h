[[cpp4r::register]] doubles regspace1_(const double& delta) {
  vec a = regspace(1, delta, 2);
  rowvec b = regspace<rowvec>(3, delta, 4);

  vec res = a + b.t();

  return as_doubles(res);
}

[[cpp4r::register]] integers randperm1_(const int& n, const int& m) {
  uvec a = randperm(n);
  uvec b = randperm(n, m);

  // concatenate a and b
  uvec c = join_cols(a, b);

  return as_integers(c);
}

[[cpp4r::register]] doubles_matrix<> eye2_(const int& n) {
  mat A = eye(n, n);  // or:  mat A(n, n, fill::eye);

  fmat B = 123.0 * eye<fmat>(n, n);

  cx_mat C = eye<cx_mat>(size(A));
  mat C_real = real(C);

  mat res = A + B + C_real;

  return as_doubles_matrix(res);
}

[[cpp4r::register]] doubles_matrix<> ones2_(const int& n) {
  vec v = ones(n);  // or: vec v(10, fill::ones);
  uvec u = ones<uvec>(n);
  rowvec r = ones<rowvec>(n);

  mat A = ones(n, n);  // or: mat A(n, n, fill::ones);
  fmat B = ones<fmat>(n, n);

  cube Q = ones(n, n, n + 1);  // or: cube Q(n, n, n + 1, fill::ones);

  mat res = diagmat(v) + diagmat(conv_to<vec>::from(u)) + diagmat(r) + A + B + Q.slice(0);

  return as_doubles_matrix(res);
}

[[cpp4r::register]] doubles_matrix<> zeros2_(const int& n) {
  vec v = zeros(n);  // or: vec v(10, fill::zeros);
  uvec u = zeros<uvec>(n);
  rowvec r = zeros<rowvec>(n);

  mat A = zeros(n, n);  // or: mat A(n, n, fill::zeros);
  fmat B = zeros<fmat>(n, n);

  cube Q = zeros(n, n, n + 1);  // or: cube Q(n, n, n + 1, fill::zeros);

  mat res = diagmat(v) + diagmat(conv_to<vec>::from(u)) + diagmat(r) + A + B + Q.slice(0);

  return as_doubles_matrix(res);
}

[[cpp4r::register]] doubles_matrix<> randu3_(const int& n) {
  double a = randu();
  double b = randu(distr_param(10, 20));

  vec v1 = randu(n);  // or vec v1(n, fill::randu);
  vec v2 = randu(n, distr_param(10, 20));

  rowvec r1 = randu<rowvec>(n);
  rowvec r2 = randu<rowvec>(n, distr_param(10, 20));

  mat A1 = randu(n, n);  // or mat A1(n, n, fill::randu);
  mat A2 = randu(n, n, distr_param(10, 20));

  fmat B1 = randu<fmat>(n, n);
  fmat B2 = randu<fmat>(n, n, distr_param(10, 20));

  mat res = diagmat(v1) + diagmat(v2) + diagmat(r1) + diagmat(r2) + A1 + A2 + B1 + B2;

  res.each_col([a](vec& x) { x += a; });
  res.each_row([b](rowvec& y) { y /= b; });

  return as_doubles_matrix(res);
}

[[cpp4r::register]] doubles_matrix<> randn3_(const int& n) {
  vec v1 = randn(n);  // or vec v1(n, fill::randn);
  vec v2 = randn(n, distr_param(10, 20));

  rowvec r1 = randn<rowvec>(n);
  rowvec r2 = randn<rowvec>(n, distr_param(10, 20));

  mat A1 = randn(n, n);  // or mat A1(n, n, fill::randn);
  mat A2 = randn(n, n, distr_param(10, 20));

  fmat B1 = randn<fmat>(n, n);
  fmat B2 = randn<fmat>(n, n, distr_param(10, 20));

  mat res = diagmat(v1) + diagmat(v2) + diagmat(r1) + diagmat(r2) + A1 + A2 + B1 + B2;

  return as_doubles_matrix(res);
}

[[cpp4r::register]] doubles_matrix<> randg3_(const int& n) {
  int a = randi();
  int b = randi(distr_param(-10, +20));

  imat A1 = randi(n, n);
  imat A2 = randi(n, n, distr_param(-10, +20));

  mat B1 = randi<mat>(n, n);
  mat B2 = randi<mat>(n, n, distr_param(-10, +20));

  mat res = A1 + A2 + B1 + B2;

  res.each_col([a](vec& x) { x *= a; });
  res.each_row([b](rowvec& y) { y -= b; });

  return as_doubles_matrix(res);
}

[[cpp4r::register]] doubles_matrix<> speye1_(const int& n) {
  sp_mat A = speye<sp_mat>(n, n);
  mat B = mat(A);
  return as_doubles_matrix(B);
}

[[cpp4r::register]] doubles_matrix<> spones1_(const int& n) {
  sp_mat A = sprandu<sp_mat>(n, n, 0.1);
  sp_mat B = spones(A);
  mat C = mat(B);
  return as_doubles_matrix(C);
}

[[cpp4r::register]] doubles_matrix<> sprandu1_(const int& n) {
  sp_mat A = sprandu<sp_mat>(n, n, 0.05);
  mat B = mat(A);
  return as_doubles_matrix(B);
}

[[cpp4r::register]] doubles_matrix<> sprandn1_(const int& n) {
  sp_mat A = sprandn<sp_mat>(n, n, 0.05);
  mat B = mat(A);
  return as_doubles_matrix(B);
}

[[cpp4r::register]] doubles_matrix<> toeplitz1_(const int& n) {
  vec a(n, fill::randu);
  vec b(n, fill::randn);

  mat X = toeplitz(a, b);
  mat Y = circ_toeplitz(a);

  mat res = X + Y;

  return as_doubles_matrix(res);
}

[[cpp4r::register]] doubles_matrix<> abs1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = abs(A);

  cx_mat X(n, n, fill::randu);
  mat Y = abs(X);

  mat res = B + Y;

  return as_doubles_matrix(res);
}

[[cpp4r::register]] double accu1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B(n, n, fill::randu);

  double x = accu(A);

  // accu(A % B) is a "multiply-and-accumulate" operation
  // as operator % performs element-wise multiplication
  double y = accu(A % B);

  return (x + y);
}

[[cpp4r::register]] doubles affmul1_(const int& n) {
  mat A(n, n + 1, fill::randu);
  vec B(n, fill::randu);

  vec C = affmul(A, B);

  return as_doubles(C);
}

[[cpp4r::register]] logicals all1_(const int& n) {
  vec V(n, fill::randu);
  mat X(n, n, fill::randu);

  // true if vector V has all non-zero elements
  bool status1 = all(V);

  // true if vector V has all elements greater than 0.5
  bool status2 = all(V > 0.5);

  // true if matrix X has all elements greater than 0.6;
  // note the use of vectorise()
  bool status3 = all(vectorise(X) > 0.6);

  // row vector indicating which columns of X have all elements greater than 0.7
  umat A = all(X > 0.7);

  writable::logicals res(4);
  res[0] = status1;
  res[1] = status2;
  res[2] = status3;
  res[3] = all(vectorise(A) == 1);  // true if all elements of A are 1

  return res;
}

[[cpp4r::register]] logicals any1_(const int& n) {
  vec V(n, fill::randu);
  mat X(n, n, fill::randu);

  // true if vector V has any non-zero elements
  bool status1 = any(V);

  // true if vector V has any elements greater than 0.5
  bool status2 = any(V > 0.5);

  // true if matrix X has any elements greater than 0.6;
  // note the use of vectorise()
  bool status3 = any(vectorise(X) > 0.6);

  // row vector indicating which columns of X have any elements greater than 0.7
  umat A = any(X > 0.7);

  writable::logicals res(4);
  res[0] = status1;
  res[1] = status2;
  res[2] = status3;
  res[3] = any(vectorise(A) == 1);  // true if any element of A is 1

  return res;
}

[[cpp4r::register]] bool approx_equal1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = A + 0.001;

  bool same1 = approx_equal(A, B, "absdiff", 0.002);

  mat C = 1000 * randu<mat>(n, n);
  mat D = C + 1;

  bool same2 = approx_equal(C, D, "reldiff", 0.1);

  bool same3 = approx_equal(C, D, "both", 2, 0.1);

  bool all_same = same1 && same2 && same3;

  return all_same;
}

[[cpp4r::register]] doubles_matrix<> arg1_(const int& n) {
  cx_mat X(n, n, fill::randu);
  mat Y = arg(X);

  return as_doubles_matrix(Y);
}

[[cpp4r::register]] double as_scalar1_(const int& n) {
  rowvec r(n, fill::randu);
  colvec q(n, fill::randu);

  mat X(n, n, fill::randu);

  // examples of expressions which have optimised implementations
  double a = as_scalar(r * q);
  double b = as_scalar(r * X * q);
  double c = as_scalar(r * diagmat(X) * q);
  double d = as_scalar(r * inv(diagmat(X)) * q);

  return (a + b + c + d);
}
