/* roxygen
@title normalise() column-wise and row-wise normalization demo
@param n integer scalar; matrix dimension
@return list with column-normalized and row-normalized matrices
@export
*/
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

/* roxygen
@title pow() element-wise power demo (scalar and matrix exponents)
@param n integer scalar; matrix dimension
@return list with squared matrix and element-wise powered matrix
@export
*/
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

/* roxygen
@title powmat() matrix power demo (two calling forms)
@param n integer scalar; matrix dimension
@return list with direct result and a sub-list with result plus success flag
@export
*/
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

/* roxygen
@title prod() column-wise and row-wise product demo
@param n integer scalar; matrix dimension
@return list with column products and row products
@export
*/
[[cpp4r::register]] list prod1_(const int& n) {
  mat A(n, n, fill::randu);

  rowvec b = prod(A, 0);
  vec c = prod(A, 1);

  writable::list res(2);
  res[0] = as_doubles(b.t());
  res[1] = as_doubles(c);

  return res;
}

/* roxygen
@title rank() matrix rank demo (two calling forms)
@param n integer scalar; matrix dimension
@return list with scalar rank and a sub-list with scalar rank plus success
  flag
@export
*/
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

/* roxygen
@title rcond() reciprocal condition number demo
@param n integer scalar; matrix dimension
@return numeric scalar: reciprocal condition number of a random matrix
@export
*/
[[cpp4r::register]] doubles rcond1_(const int& n) {
  mat A(n, n, fill::randu);
  return doubles({rcond(A)});
}

/* roxygen
@title repelem() element repetition demo
@param n integer scalar; matrix dimension
@return list with original and repeated (2x rows, 3x columns) matrix
@export
*/
[[cpp4r::register]] list repelem1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = repelem(A, 2, 3);

  writable::list res(2);
  res[0] = as_doubles_matrix(A);
  res[1] = as_doubles_matrix(B);

  return res;
}

/* roxygen
@title repmat() matrix tiling demo
@param n integer scalar; matrix dimension
@return list with original and tiled (2x rows, 3x columns) matrix
@export
*/
[[cpp4r::register]] list repmat1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = repmat(A, 2, 3);

  writable::list res(2);
  res[0] = as_doubles_matrix(A);
  res[1] = as_doubles_matrix(B);

  return res;
}

/* roxygen
@title reshape() functional form demo
@param n integer scalar; base matrix dimension
@return list with three matrices: original and two reshaped versions
@export
*/
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

/* roxygen
@title resize() functional form demo
@param n integer scalar; base matrix dimension
@return list with three matrices: original and two resized versions
@export
*/
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

/* roxygen
@title reverse() row-wise and column-wise reversal demo
@param n integer scalar; matrix dimension
@return list with original, row-reversed, and column-reversed matrix
@export
*/
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

/* roxygen
@title roots() polynomial root finding demo
@param n integer scalar; polynomial degree
@return complex vector (N-1): roots of a random degree-(N-1) polynomial
@export
*/
[[cpp4r::register]] complexes roots1_(const int& n) {
  // y = p_1*x^n + p_2*x^(n-1) + ... + p_(n-1)*x + p_n
  // p_1, ..., p_n are random numbers
  vec y(n, 1, fill::randu);

  // note that mat and cx_mat operate directly
  // but vec and cx_vec require conv_to<...>::from()
  cx_vec z = roots(conv_to<cx_vec>::from(y));

  return as_complexes(z);
}

/* roxygen
@title shift() element shifting demo (negative and positive)
@param n integer scalar; matrix dimension
@return list with original, left-shifted, and right-shifted matrix
@export
*/
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

/* roxygen
@title shuffle() random row shuffling demo
@param n integer scalar; matrix dimension
@return list with original and shuffled matrix
@export
*/
[[cpp4r::register]] list shuffle1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = shuffle(A);

  writable::list res(2);
  res[0] = as_doubles_matrix(A);
  res[1] = as_doubles_matrix(B);

  return res;
}

/* roxygen
@title size() object size operations demo
@param n integer scalar; base matrix dimension
@return list of 7 matrices illustrating size() in construction, assignment,
  subview access, addition, and multiplication
@export
*/
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

/* roxygen
@title sort() ascending/descending column and row sort demo
@param n integer scalar; matrix dimension
@return list of 5 matrices: original, col-asc, col-desc, row-asc, row-desc
@export
*/
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

/* roxygen
@title sort_index() ascending and descending sort index demo
@param n integer scalar; matrix dimension
@return list with original matrix and two index vectors
@export
*/
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

/* roxygen
@title sqrtmat() matrix square root demo (two calling forms)
@param n integer scalar; matrix dimension
@return list with original matrix, two complex square roots, and success flag
@export
*/
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

/* roxygen
@title sqrtmat_sympd() symmetric positive definite matrix square root demo
@param n integer scalar; matrix dimension
@return numeric matrix (N*N): real square root of a sym-pos-def matrix
@export
*/
[[cpp4r::register]] doubles_matrix<> sqrtmat_sympd1_(const int& n) {
  mat A(n, n, fill::randu);
  A = A * A.t();  // make A symmetric positive definite

  mat B = sqrtmat_sympd(A);

  return as_doubles_matrix(B);
}

/* roxygen
@title sum() column-wise and row-wise summation demo
@param n integer scalar; matrix dimension
@return list with row sums, column sums, and overall sum
@export
*/
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

/* roxygen
@title sum() column-wise and row-wise summation alternative form demo
@param n integer scalar; matrix dimension
@return list with row sums, column sums, and overall sum
@export
*/
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
