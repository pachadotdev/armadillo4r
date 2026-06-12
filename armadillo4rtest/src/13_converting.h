////////////////////////////////////////////////////////////////
// R to Armadillo: Matrices
////////////////////////////////////////////////////////////////

/* roxygen
@title R-to-Armadillo matrix conversion demo (double, int, float)
@param x numeric matrix
@param xi integer matrix
@return numeric matrix: A * t(A) where A is the double matrix
@export
*/
[[cpp4r::register]]
doubles_matrix<> mat_demo_(const doubles_matrix<>& x, const integers_matrix<>& xi) {
  mat A = as_Mat(x);      // double matrix
  imat Ai = as_imat(xi);  // signed int matrix
  umat Au = as_umat(xi);  // unsigned int matrix
  fmat Af = as_fmat(x);   // float matrix

  (void)Ai;
  (void)Au;
  (void)Af;  // suppress unused warnings

  return as_doubles_matrix(A * A.t());
}

////////////////////////////////////////////////////////////////
// R to Armadillo: Vectors
////////////////////////////////////////////////////////////////

/* roxygen
@title R-to-Armadillo vector conversion demo (double and unsigned int)
@param y numeric vector
@param yi integer vector
@return numeric vector: element-wise square of the input
@export
*/
[[cpp4r::register]]
doubles vec_demo_(const doubles& y, const integers& yi) {
  vec v = as_Col(y);      // double column vector
  uvec vu = as_uvec(yi);  // unsigned int column vector

  (void)vu;

  return as_doubles(v % v);  // element-wise square
}

////////////////////////////////////////////////////////////////
// R to Armadillo: Cubes
////////////////////////////////////////////////////////////////

/* roxygen
@title Convert a list of matrices to a cube and compute column means per slice
@param slices list of numeric matrices (all same dimensions)
@return numeric matrix (N_slices * N_cols): column means for each slice
@export
*/
[[cpp4r::register]]
doubles_matrix<> cube_col_means_(const list& slices) {
  cube C = as_Cube(slices);

  mat result(C.n_slices, C.n_cols);
  for (uword s = 0; s < C.n_slices; ++s) {
    result.row(s) = mean(C.slice(s), 0);
  }

  return as_doubles_matrix(result);
}

////////////////////////////////////////////////////////////////
// R to Armadillo: Fields
////////////////////////////////////////////////////////////////

/* roxygen
@title Normalize each matrix in a list via field<mat>
@param mats list of numeric matrices
@return list of normalized numeric matrices
@export
*/
[[cpp4r::register]]
list field_mat_demo_(const list& mats) {
  field<mat> F = as_field_mat(mats);

  for (uword i = 0; i < F.n_elem; ++i) {
    F(i) = normalise(F(i));
  }

  return as_doubles_matrix_field(F);
}

/* roxygen
@title Round-trip list of integer matrices via field<imat>
@param mats list of integer matrices
@return list of integer matrices identical to input
@export
*/
[[cpp4r::register]]
list field_imat_demo_(const list& mats) {
  field<imat> F = as_field_imat(mats);

  // roundtrip: no-op transformation
  return as_integers_matrix_field(F);
}

/* roxygen
@title Scale each vector in a list by 2 via field<vec>
@param vecs list of numeric vectors
@return list of numeric vectors, each scaled by 2
@export
*/
[[cpp4r::register]]
list field_vec_demo_(const list& vecs) {
  field<vec> F = as_field_vec(vecs);

  for (uword i = 0; i < F.n_elem; ++i) {
    F(i) = F(i) * 2.0;
  }

  return as_doubles_field(F);
}

/* roxygen
@title Append "!" to each string
@param x character vector
@return character vector with "!" appended to every element
@export
*/
[[cpp4r::register]]
strings field_str_demo_(const strings& x) {
  field<std::string> F = as_field_str(x);

  // append "!" to each string
  for (uword i = 0; i < F.n_elem; ++i) {
    F(i) = F(i) + "!";
  }

  return as_strings_field(F);
}

////////////////////////////////////////////////////////////////
// Armadillo to R: Matrices
////////////////////////////////////////////////////////////////

/* roxygen
@title Armadillo-to-R matrix conversion demo: t(A) * A
@param x numeric matrix
@return numeric matrix: crossproduct t(x) * x
@export
*/
[[cpp4r::register]]
doubles_matrix<> mat_out_demo_(const doubles_matrix<>& x) {
  mat A = as_Mat(x);
  return as_doubles_matrix(A.t() * A);
}

////////////////////////////////////////////////////////////////
// Armadillo to R: Vectors
////////////////////////////////////////////////////////////////

/* roxygen
@title Armadillo-to-R vector conversion demo: normalise()
@param y numeric vector
@return numeric vector: L2-normalized input vector
@export
*/
[[cpp4r::register]]
doubles vec_out_demo_(const doubles& y) {
  return as_doubles(normalise(as_Col(y)));
}

////////////////////////////////////////////////////////////////
// Armadillo to R: Cubes
////////////////////////////////////////////////////////////////

/* roxygen
@title Create a random cube and return it as a list of matrices
@param n_rows integer scalar; number of rows per slice
@param n_cols integer scalar; number of columns per slice
@param n_slices integer scalar; number of slices
@return list of N_slices numeric matrices (each N_rows * N_cols)
@export
*/
[[cpp4r::register]]
list random_cube_(const int n_rows, const int n_cols, const int n_slices) {
  cube C(n_rows, n_cols, n_slices, fill::randn);
  return as_doubles_matrix_list(C);
}

/* roxygen
@title Round-trip list of matrices via Cube<int>
@param slices list of integer matrices
@return list of integer matrices identical to input
@export
*/
[[cpp4r::register]]
list integer_cube_roundtrip_(const list& slices) {
  Cube<int> C = as_icube(slices);
  return as_integers_matrix_list(C);
}

////////////////////////////////////////////////////////////////
// Armadillo to R: Fields (build_field_ uses randn so needs RNG)
////////////////////////////////////////////////////////////////

/* roxygen
@title Build a field of random vectors of specified sizes
@param sizes integer vector of vector lengths
@return list of numeric vectors, each filled with standard normal values
@export
*/
[[cpp4r::register]]
list build_field_(const integers& sizes) {
  field<vec> F(sizes.size());

  for (uword i = 0; i < F.n_elem; ++i) {
    F(i) = randn<vec>(sizes[static_cast<int>(i)]);  // random vector of length sizes[i]
  }

  return as_doubles_field(F);
}

////////////////////////////////////////////////////////////////
// Armadillo to R: as_sexp demo
////////////////////////////////////////////////////////////////

/* roxygen
@title Sort a vector using cpp4r::as_sexp() for the return value
@param y numeric vector
@return numeric vector: sorted in ascending order
@export
*/
[[cpp4r::register]]
SEXP as_sexp_demo_(const doubles& y) {
  return cpp4r::as_sexp(arma::sort(as_Col(y)));
}
