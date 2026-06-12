/* roxygen
@title replace() NaN-with-zero demo
@param n integer scalar; matrix dimension
@return numeric matrix (N*N) with diagonal NaNs replaced by zero
@export
*/
[[cpp4r::register]] doubles_matrix<> replace1_(const int& n) {
  mat A(n, n, fill::randu);  // create a random matrix

  A.diag().fill(datum::nan);  // set the diagonal with NaN values
  A.replace(datum::nan, 0);   // replace each NaN with 0

  return as_doubles_matrix(A);  // Convert from C++ to R
}

/* roxygen
@title clamp() value-clamping demo
@param n integer scalar; matrix dimension
@return numeric matrix (N*N) with values clamped to the interval 0.2 to 0.8
@export
*/
[[cpp4r::register]] doubles_matrix<> clamp1_(const int& n) {
  mat A(n, n, fill::ones);  // create a random matrix
  A.diag().fill(0.1);       // set the diagonal with 0.1 values

  A.clamp(0.2, 0.8);  // clamp values to the [0.2, 0.8] interval

  return as_doubles_matrix(A);  // Convert from C++ to R
}

/* roxygen
@title transform() element-wise function application demo
@param n integer scalar; matrix dimension
@return numeric matrix (N*N) with 122 added to every element
@export
*/
[[cpp4r::register]] doubles_matrix<> transform1_(const int& n) {
  mat A(n, n, fill::ones);  // create a matrix filled with ones
  A.transform([](double val) { return (val + 122.0); });
  return as_doubles_matrix(A);  // Convert from C++ to R
}

/* roxygen
@title for_each() iteration demo on dense, sparse, and field containers
@param n integer scalar; container dimension
@return numeric matrix (N*N): sum of modified dense matrix, sparse matrix,
  and two zero field matrices
@export
*/
[[cpp4r::register]] doubles_matrix<> for_each1_(const int& n) {
  // add 122 to each element in a dense matrix, the '&' is important
  mat D(n, n, fill::ones);
  D.for_each([](mat::elem_type& val) { val += 122.0; });

  // add 122 to each non-zero element in a sparse matrix
  sp_mat S;
  S.sprandu(n, n, 1.0);
  S.for_each([](sp_mat::elem_type& val) { val += 123.0; });

  // set the size of all matrices in a field
  field<mat> F(2, 2);
  F.for_each([n](mat& X) { X.zeros(n, n); });  // capture n for the lambda

  mat res = D + S + F(0) + F(1);

  return as_doubles_matrix(res);  // Convert from C++ to R
}

/* roxygen
@title set_size() memory allocation demo
@param n integer scalar; container dimension
@return numeric vector: sum of first columns of two matrices plus a vector,
  all of size N
@export
*/
[[cpp4r::register]] doubles set_size1_(const int& n) {
  mat A;
  A.set_size(n, n);  // or:  mat A(n, n, fill::none);

  mat B;
  B.set_size(size(A));  // or:  mat B(size(A), fill::none);

  vec C;
  C.set_size(n);  // or:  vec v(n, fill::none);

  A.fill(1.0);  // set all elements to 1.0
  B.fill(2.0);  // set all elements to 2.0
  C.fill(3.0);  // set all elements to 3.0

  vec res = A.col(0) + B.col(1) + C;

  return as_doubles(res);  // Convert from C++ to R
}

/* roxygen
@title reshape() dimension reordering demo
@param n integer scalar; base dimension
@return numeric matrix ((N-1)*(N+1)) reshaped from an (N+1)*(N-1) matrix
@export
*/
[[cpp4r::register]] doubles_matrix<> reshape1_(const int& n) {
  mat A(n + 1, n - 1, fill::randu);
  A.reshape(n - 1, n + 1);
  return as_doubles_matrix(A);  // Convert from C++ to R
}

/* roxygen
@title resize() dimension change demo
@param n integer scalar; base dimension
@return numeric matrix ((N-1)*(N+1)) resized from an (N+1)*(N-1) matrix
@export
*/
[[cpp4r::register]] doubles_matrix<> resize1_(const int& n) {
  mat A(n + 1, n - 1, fill::randu);
  A.resize(n - 1, n + 1);
  return as_doubles_matrix(A);  // Convert from C++ to R
}

/* roxygen
@title copy_size() demo
@param n integer scalar; matrix dimension
@return named integer vector with `n_rows` and `n_cols` of the copied matrix
@export
*/
[[cpp4r::register]] integers copy_size1_(const int& n) {
  mat A(n, n, fill::randu);

  mat B;
  B.copy_size(A);

  int N = B.n_rows;
  int M = B.n_cols;

  writable::integers res({N, M});
  res.attr("names") = strings({"n_rows", "n_cols"});

  return as_integers(res);  // Convert from C++ to R
}

/* roxygen
@title reset() matrix clearing demo
@param n integer scalar; initial matrix dimension
@return named integer vector with `n_rows` and `n_cols` after reset (both 0)
@export
*/
[[cpp4r::register]] integers reset1_(const int& n) {
  mat A(n, n, fill::randu);
  A.reset();

  int N = A.n_rows;
  int M = A.n_cols;

  writable::integers res({N, M});
  res.attr("names") = strings({"n_rows", "n_cols"});

  return as_integers(res);  // Convert from C++ to R
}

/* roxygen
@title Submatrix and conditional element access demo
@param n integer scalar; matrix dimension (>= 5)
@return numeric matrix (5*5) after subview assignments and element modifications
@export
*/
[[cpp4r::register]] doubles_matrix<> subview1_(const int& n) {
  mat A(n, n, fill::zeros);

  A.submat(0, 1, 2, 3) = randu<mat>(3, 3);
  A(span(0, 2), span(1, 3)) = randu<mat>(3, 3);
  A(0, 1, size(3, 3)) = randu<mat>(3, 3);

  mat B = A.submat(0, 1, 2, 3);
  mat C = A(span(0, 2), span(1, 3));
  mat D = A(0, 1, size(3, 3));

  A.col(1) = randu<mat>(5, 1);
  A(span::all, 1) = randu<mat>(5, 1);

  mat X(5, 5, fill::randu);

  // get all elements of X that are greater than 0.5
  vec q = X.elem(find(X > 0.5));

  // add 123 to all elements of X greater than 0.5
  X.elem(find(X > 0.5)) += 123.0;

  // set four specific elements of X to 1
  uvec indices = {2, 3, 6, 8};

  X.elem(indices) = ones<vec>(4);

  // add 123 to the last 5 elements of vector a
  vec a(10, fill::randu);
  a.tail(5) += 123.0;

  // add 123 to the first 3 elements of column 2 of X
  X.col(2).head(3) += 123;

  return as_doubles_matrix(X);  // Convert from C++ to R
}

/* roxygen
@title Subcube and slice subview access demo
@param n integer scalar; cube row/column dimension
@return numeric matrix: slice 0 plus slice 1 of a cube after subview
  assignments and conditional modifications
@export
*/
[[cpp4r::register]] doubles_matrix<> subview2_(const int& n) {
  cube A(n, 3, 4, fill::randu);

  mat B = A.slice(1);  // each slice is a matrix

  A.slice(0)(1, 2) = 99.0;

  A.subcube(0, 0, 1, 1, 1, 2) = randu<cube>(2, 2, 2);
  A(span(0, 1), span(0, 1), span(1, 2)) = randu<cube>(2, 2, 2);
  A(0, 0, 1, size(2, 2, 2)) = randu<cube>(2, 2, 2);

  // add 123 to all elements of A greater than 0.5
  A.elem(find(A > 0.5)) += 123.0;

  cube C = A.head_slices(2);  // get first two slices

  A.head_slices(2) += 123.0;

  mat res = A.slice(0) + B + C.slice(1);

  return as_doubles_matrix(res);  // Convert from C++ to R
}

/* roxygen
@title Diagonal extraction and manipulation demo
@param n integer scalar; matrix dimension
@return numeric vector: sum of modified sparse and dense diagonals
@export
*/
[[cpp4r::register]] doubles diagonal1_(const int& n) {
  mat X(n, n, fill::randu);

  vec A = X.diag();             // extract the main diagonal
  double B = accu(X.diag(1));   // sum of elements on the first upper diagonal
  double C = accu(X.diag(-1));  // sum of elements on the first lower diagonal

  X.diag() = randu<vec>(n);
  X.diag() += A;
  X.diag() /= B;
  X.diag() *= C;

  sp_mat S = sprandu<sp_mat>(n, n, 0.0);
  S.diag().ones();

  vec v(S.diag());  // copy sparse diagonal to dense vector
  v += X.diag();

  return as_doubles(v);  // Convert from C++ to R
}

/* roxygen
@title each_col() broadcast demo
@param n integer scalar; number of rows
@return numeric matrix (N*(N+1)): result of column-wise broadcasts and
  lambda operations
@export
*/
[[cpp4r::register]] doubles_matrix<> each_col1_(const int& n) {
  mat X(n, n + 1, fill::ones);

  // create a vector with n elements ranging from 5 to 10
  vec v = linspace<vec>(5, 10, n);

  // in-place addition of v to each column vector of X
  X.each_col() += v;

  // generate Y by adding v to each column vector of X
  mat Y = X.each_col() + v;

  // subtract v from columns 1 and 2 of X
  X.cols(0, 1).each_col() -= v;

  uvec indices(2);
  indices(0) = 1;
  indices(1) = 2;

  X.each_col(indices) = v;  // copy v to columns 1 and 2 of X

  // lambda function with non-const vector
  X.each_col([](vec& a) { 2 * a; });

  const mat& XX = X;

  // lambda function with const vector
  XX.each_col([](const vec& b) { 3 * b; });

  mat res = X + Y + XX;

  return as_doubles_matrix(res);  // Convert from C++ to R
}

/* roxygen
@title each_row() broadcast demo
@param n integer scalar; number of columns
@return numeric matrix ((N+1)*N): result of row-wise broadcasts and
  lambda operations
@export
*/
[[cpp4r::register]] doubles_matrix<> each_row1_(const int& n) {
  mat X(n + 1, n, fill::ones);

  // create a vector with n elements ranging from 5 to 10
  rowvec v = linspace<rowvec>(5, 10, n);

  // in-place addition of v to each rows vector of X
  X.each_row() += v;

  // generate Y by adding v to each rows vector of X
  mat Y = X.each_row() + v;

  // subtract v from rows 1 and 2 of X
  X.rows(0, 1).each_row() -= v;

  uvec indices(2);
  indices(0) = 1;
  indices(1) = 2;

  X.each_row(indices) = v;  // copy v to columns 1 and 2 of X

  // lambda function with non-const vector
  X.each_row([](rowvec& a) { a / 2; });

  const mat& XX = X;

  // lambda function with const vector
  XX.each_row([](const rowvec& b) { b / 3; });

  mat res = X + Y + XX;

  return as_doubles_matrix(res);  // Convert from C++ to R
}

/* roxygen
@title each_slice() broadcast demo
@param n integer scalar; cube row dimension
@return numeric matrix (N*(N+1)): sum of all slices after slice-wise
  broadcasts and lambda operations
@export
*/
[[cpp4r::register]] doubles_matrix<> each_slice1_(const int& n) {
  cube C(n, n + 1, 6, fill::randu);

  mat M = repmat(linspace<vec>(1, n, n), 1, n + 1);

  C.each_slice() += M;  // in-place addition of M to each slice of C

  cube D = C.each_slice() + M;  // generate D by adding M to each slice of C

  // sum all slices of D into a single n x (n + 1) matrix
  mat D_flat = sum(D, 2);

  uvec indices(2);
  indices(0) = 2;
  indices(1) = 4;

  C.each_slice(indices) = M;              // copy M to slices 2 and 4 in C
  C.each_slice([](mat& X) { X * 2.0; });  // lambda function with non-const matrix
  mat C_flat = sum(C, 2);

  const cube& CC = C;
  CC.each_slice([](const mat& X) { X / 3.0; });  // lambda function with const matrix

  mat CC_flat = sum(CC, 2);

  mat res = C_flat + D_flat + CC_flat;

  return as_doubles_matrix(res);  // Convert from C++ to R
}

/* roxygen
@title set_real() real-part assignment demo
@param n integer scalar; base matrix dimension
@return complex matrix ((N+1)*(N-1)) with real part set from a random matrix
@export
*/
[[cpp4r::register]] complexes_matrix<> set_real1_(const int& n) {
  mat A(n + 1, n - 1, fill::randu);

  cx_mat C(n + 1, n - 1, fill::zeros);

  C.set_real(A);

  return as_complexes_matrix(C);  // Convert from C++ to R
}

/* roxygen
@title cx_mat construction from two real matrices demo
@param n integer scalar; base matrix dimension
@return complex matrix ((N-1)*(N+1)) constructed from two random real matrices
@export
*/
[[cpp4r::register]] complexes_matrix<> set_real2_(const int& n) {
  mat A(n - 1, n + 1, fill::randu);
  mat B(n - 1, n + 1, fill::randu);

  cx_mat C = cx_mat(A, B);

  return as_complexes_matrix(C);  // Convert from C++ to R
}

/* roxygen
@title set_imag() imaginary-part assignment demo
@param n integer scalar; base matrix dimension
@return complex matrix ((N+1)*(N-1)) with imaginary part set from a random matrix
@export
*/
[[cpp4r::register]] complexes_matrix<> set_imag1_(const int& n) {
  mat B(n + 1, n - 1, fill::randu);

  cx_mat C(n + 1, n - 1, fill::zeros);

  C.set_imag(B);

  return as_complexes_matrix(C);  // Convert from C++ to R
}

/* roxygen
@title insert_cols() column insertion demo
@param n integer scalar; base matrix dimension
@return numeric matrix (3N-1)*(3N-1) with columns inserted
@export
*/
[[cpp4r::register]] doubles_matrix<> insert_columns1_(const int& n) {
  mat A(n, n * 2, fill::randu);
  mat B(n, n - 1, fill::ones);

  // at column n - 1, insert a copy of B
  // A will now have 3n - 1 columns
  A.insert_cols(n - 1, B);

  // at column 1, insert 2n zeroed columns
  // B will now have 3n - 1 columns
  B.insert_cols(1, n * 2);

  mat res = A + B;

  return as_doubles_matrix(res);  // Convert from C++ to R
}

/* roxygen
@title insert_rows() row insertion demo
@param n integer scalar; base matrix dimension
@return numeric matrix (3N-1)*(3N-1) with rows inserted
@export
*/
[[cpp4r::register]] doubles_matrix<> insert_rows1_(const int& n) {
  mat A(n * 2, n, fill::randu);
  mat B(n - 1, n, fill::ones);

  // at row n - 1, insert a copy of B
  // A will now have 3n - 1 rows
  A.insert_rows(n - 1, B);

  // at row 1, insert 2n zeroed rows
  // B will now have 3n - 1 rows
  B.insert_rows(1, n * 2);

  mat res = A + B;

  return as_doubles_matrix(res);  // Convert from C++ to R
}
