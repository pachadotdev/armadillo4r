/* roxygen
@title insert_slices() cube insertion demo
@param n integer scalar; cube dimension
@return numeric matrix (N*N): element-wise sum over all slices of two
  modified cubes
@export
*/
[[cpp4r::register]] doubles_matrix<> insert_slices1_(const int& n) {
  cube A(n, n, n * 2, fill::randu);
  cube B(n, n, n - 1, fill::ones);

  // At slice n - 1, insert a copy of B
  // A will now have 3n - 1 slices
  A.insert_slices(n - 1, B);

  // At slice 1, insert 2n zeroed slices
  // B will now have 3n - 1 slices
  B.insert_slices(1, n * 2);

  mat res = sum(A + B, 2);

  return as_doubles_matrix(res);  // Convert from C++ to R
}

/* roxygen
@title shed_col() / shed_cols() column removal demo
@param n integer scalar; initial number of rows
@return numeric matrix after removing 4 columns from an N*(5N) matrix
@export
*/
[[cpp4r::register]] doubles_matrix<> shed_columns1_(const int& n) {
  mat A(n, n * 5, fill::randu);

  // remove the first column
  A.shed_col(0);

  // remove columns 1 and 2
  A.shed_cols(0, 1);

  // remove columns 2 and 4
  uvec indices(2);
  indices(0) = 1;
  indices(1) = 3;
  A.shed_cols(indices);

  return as_doubles_matrix(A);  // Convert from C++ to R
}

/* roxygen
@title shed_row() / shed_rows() row removal demo
@param n integer scalar; initial number of columns
@return numeric matrix after removing 4 rows from a (5N)*N matrix
@export
*/
[[cpp4r::register]] doubles_matrix<> shed_rows1_(const int& n) {
  mat A(n * 5, n, fill::randu);

  // remove the first row
  A.shed_row(0);

  // remove rows 1 and 2
  A.shed_rows(0, 1);

  // remove rows 2 and 4
  uvec indices(2);
  indices(0) = 1;
  indices(1) = 3;
  A.shed_rows(indices);

  return as_doubles_matrix(A);  // Convert from C++ to R
}

/* roxygen
@title shed_slice() / shed_slices() cube slice removal demo
@param n integer scalar; cube dimension
@return numeric matrix (N*N): sum over remaining slices after removing 4
@export
*/
[[cpp4r::register]] doubles_matrix<> shed_slices1_(const int& n) {
  cube A(n, n, n * 5, fill::randu);

  // remove the first slice
  A.shed_slice(0);

  // remove slices 1 and 2
  A.shed_slices(0, 1);

  // remove slices 2 and 4
  uvec indices(2);
  indices(0) = 1;
  indices(1) = 3;
  A.shed_slices(indices);

  mat res = sum(A, 2);

  return as_doubles_matrix(res);  // Convert from C++ to R
}

/* roxygen
@title swap_cols() column swapping demo
@param n integer scalar; number of rows
@return numeric matrix (N*(5N)) after two column swaps
@export
*/
[[cpp4r::register]] doubles_matrix<> swap_columns1_(const int& n) {
  mat A(n, n * 5, fill::randu);

  // swap columns 1 and 2
  A.swap_cols(0, 1);

  // swap columns 2 and 4
  A.swap_cols(1, 3);

  return as_doubles_matrix(A);  // Convert from C++ to R
}

/* roxygen
@title swap_rows() row swapping demo
@param n integer scalar; number of columns
@return numeric matrix ((5N)*N) after two row swaps
@export
*/
[[cpp4r::register]] doubles_matrix<> swap_rows1_(const int& n) {
  mat A(n * 5, n, fill::randu);

  // swap rows 1 and 2
  A.swap_rows(0, 1);

  // swap rows 2 and 4
  A.swap_rows(1, 3);

  return as_doubles_matrix(A);  // Convert from C++ to R
}

/* roxygen
@title swap() matrix swap demo
@param n integer scalar; dimension
@return numeric matrix: result is the original `B` after swapping contents
  with `A`
@export
*/
[[cpp4r::register]] doubles_matrix<> swap1_(const int& n) {
  mat A(n, n + 1, fill::zeros);
  mat B(n * 2, n - 1, fill::ones);

  A.swap(B);

  return as_doubles_matrix(A);  // Convert from C++ to R
}

/* roxygen
@title memptr() raw memory pointer access demo
@param n integer scalar; matrix dimension
@return numeric matrix (N*N) with each element increased by 123 plus the
  corresponding element of a second random matrix
@export
*/
[[cpp4r::register]] doubles_matrix<> memptr1_(const int& n) {
  mat A(n, n, fill::randu);
  const mat B(n, n, fill::randu);

  double* A_mem = A.memptr();
  const double* B_mem = B.memptr();

  // alter A_mem
  // B_mem is const, so it cannot be altered
  for (int i = 0; i < n * n; ++i) {
    A_mem[i] += 123.0 + B_mem[i];
  }

  return as_doubles_matrix(A);  // Convert from C++ to R
}

/* roxygen
@title colptr() column memory pointer access demo
@param n integer scalar; matrix dimension
@return numeric matrix (N*N) with first column elements increased by 123
@export
*/
[[cpp4r::register]] doubles_matrix<> colptr1_(const int& n) {
  mat A(n, n, fill::randu);

  // pointer to the memory of the first column of A
  double* Acol1_mem = A.colptr(0);

  // alter memory
  for (int i = 0; i < n; ++i) {
    Acol1_mem[i] += 123.0;
  }

  return as_doubles_matrix(A);  // Convert from C++ to R
}

/* roxygen
@title Element and column iterator demo on a matrix
@param n integer scalar; matrix row dimension
@return numeric matrix (N*(N+1)) after iterating all elements and column 1-N
@export
*/
[[cpp4r::register]] doubles_matrix<> iterators1_(const int& n) {
  mat X(n, n + 1, fill::randu);

  mat::iterator it = X.begin();
  mat::iterator it_end = X.end();

  for (; it != it_end; ++it) {
    (*it) += 123.0;
  }

  mat::col_iterator col_it = X.begin_col(1);    // start of column 1
  mat::col_iterator col_it_end = X.end_col(n);  //   end of column n

  for (; col_it != col_it_end; ++col_it) {
    (*col_it) = 321.0;
  }

  return as_doubles_matrix(X);  // Convert from C++ to R
}

/* roxygen
@title Element and slice iterator demo on a cube
@param n integer scalar; cube dimension
@return numeric matrix (N*(N+1)): sum over all slices after iterating
@export
*/
[[cpp4r::register]] doubles_matrix<> iterators2_(const int& n) {
  cube X(n, n + 1, n + 2, fill::randu);

  cube::iterator it = X.begin();
  cube::iterator it_end = X.end();

  for (; it != it_end; ++it) {
    (*it) += 123.0;
  }

  cube::slice_iterator s_it = X.begin_slice(1);    // start of slice 1
  cube::slice_iterator s_it_end = X.end_slice(n);  // end of slice n

  for (; s_it != s_it_end; ++s_it) {
    (*s_it) = 321.0;
  }

  mat res = sum(X, 2);

  return as_doubles_matrix(res);  // Convert from C++ to R
}

#ifndef ARMADILLO4R_NO_SPARSE

/* roxygen
@title Sparse matrix element iterator demo
@param n integer scalar; matrix row dimension
@return numeric matrix (N*(2N)): sparse matrix after incrementing all
  non-zero elements by 123
@export
*/
[[cpp4r::register]] doubles_matrix<> iterators3_(const int& n) {
  sp_mat X = sprandu<sp_mat>(n, n * 2, 0.1);

  sp_mat::iterator it = X.begin();
  sp_mat::iterator it_end = X.end();

  for (; it != it_end; ++it) {
    (*it) += 123.0;
  }

  return as_doubles_matrix(X);  // Convert from C++ to R
}

#endif  // ARMADILLO4R_NO_SPARSE

/* roxygen
@title Range-based for loop over a subview demo
@param n integer scalar; matrix dimension
@return numeric matrix (N*N) with subview elements set to 123
@export
*/
[[cpp4r::register]] doubles_matrix<> iterators4_(const int& n) {
  mat X(n, n, fill::randu);

  for (double& val : X(span(0, 1), span(1, 1))) {
    val = 123.0;
  }

  return as_doubles_matrix(X);  // Convert from C++ to R
}

/* roxygen
@title front() and back() compatibility demo
@param n integer scalar; vector length
@return named numeric vector with `front` and `back` elements
@export
*/
[[cpp4r::register]] doubles compatibility1_(const int& n) {
  vec X(n, fill::randu);

  writable::doubles res = {X.front(), X.back()};

  res.attr("names") = strings({"front", "back"});

  return res;
}

/* roxygen
@title clear() matrix clearing demo
@param n integer scalar; initial matrix dimension
@return named integer vector with row count `before` (N) and `after` (0)
@export
*/
[[cpp4r::register]] integers compatibility2_(const int& n) {
  mat X(n, n, fill::randu);

  writable::integers res(2);
  res[0] = X.n_rows;

  X.clear();
  res[1] = X.n_rows;

  res.attr("names") = strings({"before", "after"});

  return res;
}

/* roxygen
@title as_col() matrix-to-column-vector conversion demo
@param n integer scalar; matrix row dimension
@return numeric vector: all elements of an N*(N+1) matrix stacked
  column-major
@export
*/
[[cpp4r::register]] doubles as_col1_(const int& n) {
  mat M(n, n + 1, fill::randu);
  vec V = M.as_col();
  return as_doubles(V);
}

/* roxygen
@title as_row() matrix-to-row-vector conversion demo
@param n integer scalar; matrix row dimension
@return numeric vector: all elements of an N*(N+1) matrix stacked row-major
@export
*/
[[cpp4r::register]] doubles as_row1_(const int& n) {
  mat M(n, n + 1, fill::randu);
  rowvec V = M.as_row();
  return as_doubles(V.t());
}

/* roxygen
@title col_as_mat() cube column extraction demo
@param n integer scalar; cube row dimension
@return list with 4 slice matrices and the extracted `col_as_mat` matrix
@export
*/
[[cpp4r::register]] list col_as_mat1_(const int& n) {
  cube C(n, n + 1, n + 2, fill::randu);
  mat M = C.col_as_mat(0);  // size n x (n + 1)

  writable::list res(5);
  res[0] = as_doubles_matrix(C.slice(0));
  res[1] = as_doubles_matrix(C.slice(1));
  res[2] = as_doubles_matrix(C.slice(2));
  res[3] = as_doubles_matrix(C.slice(3));
  res[4] = as_doubles_matrix(M);

  res.attr("names") = strings({"slice0", "slice1", "slice2", "slice3", "col_as_mat"});

  return res;
}

/* roxygen
@title row_as_mat() cube row extraction demo
@param n integer scalar; cube row dimension
@return list with 4 slice matrices and the extracted `row_as_mat` matrix
@export
*/
[[cpp4r::register]] list row_as_mat1_(const int& n) {
  cube C(n, n + 1, n + 2, fill::randu);
  mat M = C.row_as_mat(0);  // size (n + 2) x (n + 1)

  writable::list res(5);
  res[0] = as_doubles_matrix(C.slice(0));
  res[1] = as_doubles_matrix(C.slice(1));
  res[2] = as_doubles_matrix(C.slice(2));
  res[3] = as_doubles_matrix(C.slice(3));
  res[4] = as_doubles_matrix(M);

  res.attr("names") = strings({"slice0", "slice1", "slice2", "slice3", "row_as_mat"});

  return res;
}

#ifndef ARMADILLO4R_NO_SPARSE

/* roxygen
@title as_dense() sparse-to-dense conversion demo
@param n integer scalar; sparse matrix dimension
@return numeric vector: dense column plus dense row-sum of a random sparse
  matrix
@export
*/
[[cpp4r::register]] doubles as_dense1_(const int& n) {
  sp_mat A;
  A.sprandu(n, n, 0.1);

  // extract column 1 of A directly into dense column vector
  colvec c = A.col(0).as_dense();

  // store the sum of each column of A directly in dense row vector
  rowvec r = sum(A).as_dense();

  return as_doubles(c + r.t());
}

#endif  // ARMADILLO4R_NO_SPARSE

/* roxygen
@title Matrix transpose demo
@param n integer scalar; matrix row dimension
@return numeric matrix ((N+1)*N): transpose of an N*(N+1) random matrix
@export
*/
[[cpp4r::register]] doubles_matrix<> transpose1_(const int& n) {
  mat A(n, n + 1, fill::randu);
  mat B = A.t();
  return as_doubles_matrix(B);
}
