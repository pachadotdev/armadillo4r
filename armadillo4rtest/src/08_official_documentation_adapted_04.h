[[cpp4r::register]] doubles_matrix<> transpose2_(const int& n) {
  sp_mat A;
  A.sprandu(n, n + 1, 0.1);
  sp_mat B = A.t();
  return as_doubles_matrix(B);
}

[[cpp4r::register]] doubles inverse1_(const doubles_matrix<>& a, const doubles b) {
  mat A = as_Mat(a);
  vec B = as_Col(b);

  mat X = inv(A);
  vec Y = X * B;

  return as_doubles(Y);
}

[[cpp4r::register]] doubles maxmin1_(const int& n) {
  mat A = randu<mat>(n, n);

  writable::doubles res(2);
  res[0] = A.max();
  res[1] = A.min();

  res.attr("names") = strings({"max", "min"});

  return res;
}

[[cpp4r::register]] doubles index_maxmin1_(const int& n) {
  mat A = randu<mat>(n, n);

  writable::doubles res(6);
  res[0] = static_cast<int>(A.index_max());
  res[1] = static_cast<int>(A.index_min());
  res[2] = A(0, 0);
  res[3] = A(1, 0);
  res[4] = A(0, 1);
  res[5] = A(1, 1);

  res.attr("names") =
      strings({"index_max", "index_min", "element0", "element1", "element2", "element3"});

  return res;
}

[[cpp4r::register]] logicals in_range1_(const int& n) {
  mat A(n, n + 1, fill::randu);

  writable::logicals res(3);
  res[0] = A.in_range(0, 0);
  res[1] = A.in_range(3, 4);
  res[2] = A.in_range(4, 5);

  res.attr("names") = strings({"in_range00", "in_range34", "in_range45"});

  return res;
}

[[cpp4r::register]] logicals is_empty1_(const int& n) {
  mat A(n, n + 1, fill::randu);

  writable::logicals res(2);
  res[0] = A.is_empty();

  A.reset();
  res[1] = A.is_empty();

  res.attr("names") = strings({"before_reset", "after_reset"});

  return res;
}

[[cpp4r::register]] logicals is_vec1_(const int& n) {
  mat A(n, 1, fill::randu);
  mat B(1, n, fill::randu);
  mat C(0, 1, fill::randu);
  mat D(1, 0, fill::randu);

  writable::logicals res(5);
  res[0] = A.is_vec();
  res[1] = A.is_colvec();
  res[2] = B.is_rowvec();
  res[3] = C.is_colvec();
  res[4] = D.is_rowvec();

  res.attr("names") = strings(
      {"Nx1_is_vec", "Nx1_is_colvec", "1xN_is_rowvec", "0x1_is_colvec", "1x0_is_rowvec"});

  return res;
}

[[cpp4r::register]] logicals is_sorted1_(const int& n) {
  vec a(n, fill::randu);
  vec b = sort(a);
  mat A(10, 10, fill::randu);

  writable::logicals res(4);
  res[0] = a.is_sorted();
  res[1] = b.is_sorted();
  res[2] = A.is_sorted("descend", 1);
  res[4] = A.is_sorted("ascend", 1);

  res.attr("names") = strings({"a_sorted", "b_sorted", "A_descend", "A_ascend"});

  return res;
}

[[cpp4r::register]] logicals is_triangular1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = trimatl(A);

  writable::logicals res(3);
  res[0] = B.is_trimatu();
  res[1] = B.is_trimatl();

  B.reset();
  res[2] = B.is_trimatu();

  res.attr("names") = strings({"is_trimatu", "is_trimatl", "is_trimatu_after_reset"});

  return res;
}

[[cpp4r::register]] logicals is_diagonal1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = diagmat(A);

  writable::logicals res(3);
  res[0] = A.is_diagmat();
  res[1] = B.is_diagmat();

  A.reset();
  res[2] = A.is_diagmat();

  res.attr("names") = strings({"A_diagmat", "B_diagmat", "A_diagmat_after_reset"});

  return res;
}

[[cpp4r::register]] logicals is_square1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = diagmat(A);

  writable::logicals res(3);
  res[0] = A.is_square();
  res[1] = B.is_square();

  A.reset();
  res[2] = A.is_square();

  res.attr("names") = strings({"A_square", "B_square", "A_square_after_reset"});

  return res;
}

[[cpp4r::register]] logicals is_symmetric1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = symmatu(A);

  writable::logicals res(3);
  res[0] = A.is_symmetric();
  res[1] = B.is_symmetric();

  A.reset();
  res[2] = A.is_symmetric();

  res.attr("names") = strings({"A_symmetric", "B_symmetric", "A_symmetric_after_reset"});

  return res;
}

[[cpp4r::register]] logicals is_hermitian1_(const int& n) {
  cx_mat A(n, n, fill::randu);
  cx_mat B = A.t() * A;

  writable::logicals res(3);
  res[0] = A.is_hermitian();
  res[1] = B.is_hermitian();

  A.reset();
  res[2] = A.is_hermitian();

  res.attr("names") = strings({"A_hermitian", "B_hermitian", "A_hermitian_after_reset"});

  return res;
}

[[cpp4r::register]] logicals is_sympd1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = A * A.t();

  writable::logicals res(3);
  res[0] = A.is_sympd(0.005);
  res[1] = B.is_sympd(0.005);

  A.reset();
  res[2] = A.is_sympd();

  res.attr("names") = strings({"A_sympd", "B_sympd", "A_sympd_after_reset"});

  return res;
}

[[cpp4r::register]] logicals is_zero1_(const int& n) {
  mat A(n, n, fill::randu);
  cube B(n, n, n, fill::zeros);
  sp_mat C(n, n);

  writable::logicals res(3);
  res[0] = A.is_zero(0.005);
  res[1] = B.is_zero(0.005);
  res[2] = C.is_zero(0.005);

  res.attr("names") = strings({"A_is_zero", "B_is_zero", "C_is_zero"});

  return res;
}

[[cpp4r::register]] logicals is_finite1_(const int& n) {
  mat A(n, n, fill::randu);
  cube B(n, n, n, fill::randu);
  sp_mat C(n, n);

  // Insert infinite values
  B(0, 0, 0) = datum::inf;
  C(0, 0) = -1.0 * datum::inf;

  writable::logicals res(3);
  res[0] = A.is_finite();
  res[1] = B.is_finite();
  res[2] = C.is_finite();

  res.attr("names") = strings({"A_is_finite", "B_is_finite", "C_is_finite"});

  return res;
}

[[cpp4r::register]] logicals has_inf1_(const int& n) {
  mat A(n, n, fill::randu);
  cube B(n, n, n, fill::randu);
  sp_mat C(n, n);

  // Insert infinite values
  B(0, 0, 0) = datum::inf;
  C(0, 0) = -1.0 * datum::inf;

  writable::logicals res(3);
  res[0] = A.has_inf();
  res[1] = B.has_inf();
  res[2] = C.has_inf();

  res.attr("names") = strings({"A_has_inf", "B_has_inf", "C_has_inf"});

  return res;
}

[[cpp4r::register]] logicals has_nan1_(const int& n) {
  mat A(n, n, fill::randu);
  cube B(n, n, n, fill::randu);
  sp_mat C(n, n);

  // Insert NaN values
  B(0, 0, 0) = datum::nan;
  C(0, 0) = -1.0 * datum::nan;

  writable::logicals res(3);
  res[0] = A.has_nan();
  res[1] = B.has_nan();
  res[2] = C.has_nan();

  res.attr("names") = strings({"A_has_nan", "B_has_nan", "C_has_nan"});

  return res;
}

[[cpp4r::register]] doubles linspace1_(const int& n) {
  vec a = linspace(1, 2, n);
  rowvec b = linspace<rowvec>(3, 4, n);

  vec res = a + b.t();

  return as_doubles(res);
}

[[cpp4r::register]] doubles logspace1_(const int& n) {
  vec a = logspace(1, 2, n);
  rowvec b = logspace<rowvec>(3, 4, n);

  vec res = a + b.t();

  return as_doubles(res);
}
