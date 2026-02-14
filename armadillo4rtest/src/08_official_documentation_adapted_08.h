[[cpp4r::register]] list normalise1_(const int& n) {
  mat A(n, n, fill::randu);

  mat B = normalise(A, 1, 0);
  mat C = normalise(A, 1, 1);

  writable::list res(2);
  res[0] = as_doubles_matrix(B);
  res[1] = as_doubles_matrix(C);

  res.attr("names") = strings({"B_norm1_cols", "C_norm1_rows"});

  return res;
}

[[cpp4r::register]] list pow1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B(n, n, fill::randu);

  mat C = pow(A, 2);
  mat D = pow(A, B);

  writable::list res(2);
  res[0] = as_doubles_matrix(C);
  res[1] = as_doubles_matrix(D);

  return res;
}

[[cpp4r::register]] list powmat1_(const int& n) {
  mat A(n, n, fill::randu);

  mat B = powmat(A, 2);  // form 1

  mat C;
  bool ok = powmat(C, A, 2);  // form 2

  writable::list res(2);
  res[0] = as_doubles_matrix(B);

  writable::list res2(2);
  res2[0] = as_doubles_matrix(C);
  res2[1] = logicals({ok});

  res[1] = res2;

  res.attr("names") = strings({"powmat_form1", "powmat_form2"});
  res2.attr("names") = strings({"result", "status"});

  return res;
}

[[cpp4r::register]] list prod1_(const int& n) {
  mat A(n, n, fill::randu);

  rowvec b = prod(A, 0);
  vec c = prod(A, 1);

  writable::list res(2);
  res[0] = as_doubles(b.t());
  res[1] = as_doubles(c);

  return res;
}

[[cpp4r::register]] list rank1_(const int& n) {
  mat A(n, n, fill::randu);

  int r1 = rank(A);

  uword r2;
  bool ok = rank(r2, A);

  writable::list res(2);
  res[0] = integers({r1});

  writable::list res2(2);
  res2[0] = integers({static_cast<int>(r2)});
  res2[1] = logicals({ok});

  res[1] = res2;

  res.attr("names") = strings({"rank1", "rank2"});
  res2.attr("names") = strings({"result", "status"});

  return res;
}

[[cpp4r::register]] doubles rcond1_(const int& n) {
  mat A(n, n, fill::randu);
  return doubles({rcond(A)});
}

[[cpp4r::register]] list repelem1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = repelem(A, 2, 3);

  writable::list res(2);
  res[0] = as_doubles_matrix(A);
  res[1] = as_doubles_matrix(B);

  return res;
}

[[cpp4r::register]] list repmat1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = repmat(A, 2, 3);

  writable::list res(2);
  res[0] = as_doubles_matrix(A);
  res[1] = as_doubles_matrix(B);

  return res;
}

[[cpp4r::register]] list reshape2_(const int& n) {
  mat A(n, n + 1, fill::randu);

  mat B = reshape(A, n + 1, n);

  mat C(n + 4, n - 1);
  C = reshape(A, size(C));

  writable::list res(3);
  res[0] = as_doubles_matrix(A);
  res[1] = as_doubles_matrix(B);
  res[2] = as_doubles_matrix(C);

  return res;
}

[[cpp4r::register]] list resize2_(const int& n) {
  mat A(n, n + 1, fill::randu);

  mat B = resize(A, n + 1, n);

  mat C(n + 4, n - 1);
  C = resize(A, size(C));

  writable::list res(3);
  res[0] = as_doubles_matrix(A);
  res[1] = as_doubles_matrix(B);
  res[2] = as_doubles_matrix(C);

  return res;
}

[[cpp4r::register]] list reverse1_(const int& n) {
  mat A(n, n, fill::randu);

  mat B = reverse(A, 0);
  mat C = reverse(A, 1);

  writable::list res(3);
  res[0] = as_doubles_matrix(A);
  res[1] = as_doubles_matrix(B);
  res[2] = as_doubles_matrix(C);

  return res;
}

[[cpp4r::register]] complexes roots1_(const int& n) {
  // y = p_1*x^n + p_2*x^(n-1) + ... + p_(n-1)*x + p_n
  // p_1, ..., p_n are random numbers
  vec y(n, 1, fill::randu);

  // note that mat and cx_mat operate directly
  // but vec and cx_vec require conv_to<...>::from()
  cx_vec z = roots(conv_to<cx_vec>::from(y));

  return as_complexes(z);
}

[[cpp4r::register]] list shift1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = shift(A, -1);
  mat C = shift(A, +1);

  writable::list res(3);
  res[0] = as_doubles_matrix(A);
  res[1] = as_doubles_matrix(B);
  res[2] = as_doubles_matrix(C);

  return res;
}

[[cpp4r::register]] list shuffle1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = shuffle(A);

  writable::list res(2);
  res[0] = as_doubles_matrix(A);
  res[1] = as_doubles_matrix(B);

  return res;
}

[[cpp4r::register]] list size1_(const int& n) {
  mat A(n, n, fill::randu);

  mat B(size(A), fill::zeros);

  mat C;
  C.randu(size(A));
  mat D = ones<mat>(size(A));

  mat E(2 * n, 2 * n, fill::ones);
  E(1, 2, size(C)) = C;  // access submatrix of E

  mat F(size(A) + size(E), fill::randu);

  mat G(size(A) * 2, fill::randu);

  writable::list res(7);

  res[0] = as_doubles_matrix(A);
  res[1] = as_doubles_matrix(B);
  res[2] = as_doubles_matrix(C);
  res[3] = as_doubles_matrix(D);
  res[4] = as_doubles_matrix(E);
  res[5] = as_doubles_matrix(F);
  res[6] = as_doubles_matrix(G);

  return res;
}

[[cpp4r::register]] list sort1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = sort(A);
  mat C = sort(A, "descend");
  mat D = sort(A, "ascend", 1);
  mat E = sort(A, "descend", 1);

  writable::list res(5);
  res[0] = as_doubles_matrix(A);
  res[1] = as_doubles_matrix(B);
  res[2] = as_doubles_matrix(C);
  res[3] = as_doubles_matrix(D);
  res[4] = as_doubles_matrix(E);

  return res;
}

[[cpp4r::register]] list sort_index1_(const int& n) {
  mat A(n, n, fill::randu);
  uvec B = sort_index(A);
  uvec C = sort_index(A, "descend");

  writable::list res(3);
  res[0] = as_doubles_matrix(A);
  res[1] = as_integers(B);
  res[2] = as_integers(C);

  return res;
}

[[cpp4r::register]] list sqrtmat1_(const int& n) {
  mat A(n, n, fill::randu);

  cx_mat B = sqrtmat(A);

  cx_mat C;
  bool ok = sqrtmat(C, A);

  writable::list res(4);

  res[0] = as_doubles_matrix(A);
  res[1] = as_complexes_matrix(B);
  res[2] = as_complexes_matrix(C);
  res[3] = logicals({ok});

  return res;
}

[[cpp4r::register]] doubles_matrix<> sqrtmat_sympd1_(const int& n) {
  mat A(n, n, fill::randu);
  A = A * A.t();  // make A symmetric positive definite

  mat B = sqrtmat_sympd(A);

  return as_doubles_matrix(B);
}

[[cpp4r::register]] list sum1_(const int& n) {
  mat A(n, n, fill::randu);

  rowvec a = sum(A, 0);
  colvec b = sum(A, 1);
  double c = accu(A);  // overall sum

  writable::list res(4);
  res[0] = as_doubles(a);
  res[1] = as_doubles(b);
  res[2] = doubles({c});

  return res;
}

[[cpp4r::register]] list sum2_(const int& n) {
  mat A(n, n, fill::randu);

  vec a = sum(A, 1);
  vec b = sum(A, 0).t();
  double c = accu(A);  // overall sum

  writable::list res(3);
  res[0] = as_doubles(a);
  res[1] = as_doubles(b);
  res[2] = doubles({c});

  return res;
}
