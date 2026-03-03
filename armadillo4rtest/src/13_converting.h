////////////////////////////////////////////////////////////////
// R to Armadillo: Matrices
////////////////////////////////////////////////////////////////

[[cpp4r::register]]
doubles_matrix<> mat_demo_(const doubles_matrix<>& x,
                           const integers_matrix<>& xi) {
  mat  A  = as_Mat(x);    // double matrix
  imat Ai = as_imat(xi);  // signed int matrix
  umat Au = as_umat(xi);  // unsigned int matrix
  fmat Af = as_fmat(x);   // float matrix

  (void)Ai; (void)Au; (void)Af;  // suppress unused warnings

  return as_doubles_matrix(A * A.t());
}

////////////////////////////////////////////////////////////////
// R to Armadillo: Vectors
////////////////////////////////////////////////////////////////

[[cpp4r::register]]
doubles vec_demo_(const doubles& y, const integers& yi) {
  vec  v  = as_Col(y);    // double column vector
  uvec vu = as_uvec(yi);  // unsigned int column vector

  (void)vu;

  return as_doubles(v % v);   // element-wise square
}

////////////////////////////////////////////////////////////////
// R to Armadillo: Cubes
////////////////////////////////////////////////////////////////

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

[[cpp4r::register]]
list field_mat_demo_(const list& mats) {
  field<mat> F = as_field_mat(mats);

  for (uword i = 0; i < F.n_elem; ++i) {
    F(i) = normalise(F(i));
  }

  return as_doubles_matrix_field(F);
}

[[cpp4r::register]]
list field_imat_demo_(const list& mats) {
  field<imat> F = as_field_imat(mats);

  // roundtrip: no-op transformation
  return as_integers_matrix_field(F);
}

[[cpp4r::register]]
list field_vec_demo_(const list& vecs) {
  field<vec> F = as_field_vec(vecs);

  for (uword i = 0; i < F.n_elem; ++i) {
    F(i) = F(i) * 2.0;
  }

  return as_doubles_field(F);
}

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

[[cpp4r::register]]
doubles_matrix<> mat_out_demo_(const doubles_matrix<>& x) {
  mat A = as_Mat(x);
  return as_doubles_matrix(A.t() * A);
}

////////////////////////////////////////////////////////////////
// Armadillo to R: Vectors
////////////////////////////////////////////////////////////////

[[cpp4r::register]]
doubles vec_out_demo_(const doubles& y) {
  return as_doubles(normalise(as_Col(y)));
}

////////////////////////////////////////////////////////////////
// Armadillo to R: Cubes
////////////////////////////////////////////////////////////////

[[cpp4r::register]]
list random_cube_(const int n_rows, const int n_cols, const int n_slices) {
  cube C(n_rows, n_cols, n_slices, fill::randn);
  return as_doubles_matrix_list(C);
}

[[cpp4r::register]]
list integer_cube_roundtrip_(const list& slices) {
  Cube<int> C = as_icube(slices);
  return as_integers_matrix_list(C);
}

////////////////////////////////////////////////////////////////
// Armadillo to R: Fields (build_field_ uses randn so needs RNG)
////////////////////////////////////////////////////////////////

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

[[cpp4r::register]]
SEXP as_sexp_demo_(const doubles& y) {
  return cpp4r::as_sexp(arma::sort(as_Col(y)));
}
