#ifdef ARMADILLO4R_SPARSE

/* roxygen
@title Convert a dgCMatrix to SpMat<double> and back
@param x sparse matrix in dgCMatrix format
@return dgCMatrix: round-trip result (values unchanged)
@export
*/
[[cpp4r::register]] SEXP test_dgCMatrix_to_SpMat(SEXP x) {
  // Convert from dgCMatrix to SpMat
  SpMat<double> A = as_SpMat(x);

  // Optional: perform some operation on A
  // For example, multiply each element by 2
  A *= 1.0;

  // Convert back to dgCMatrix and return
  return as_dgCMatrix(A);
}

/* roxygen
@title Convert any sparse Matrix to dgCMatrix via SpMat<double>
@param x sparse matrix (any CsparseMatrix, RsparseMatrix, or TsparseMatrix)
@return dgCMatrix: round-trip conversion result
@export
*/
[[cpp4r::register]] SEXP test_sparse_to_dgCMatrix(SEXP x) {
  // Accepts any sparse Matrix object (CsparseMatrix, RsparseMatrix,
  // TsparseMatrix, symmetric, triangular, ...) and round-trips it as a
  // dgCMatrix.
  SpMat<double> A = as_SpMat(x);
  return as_dgCMatrix(A);
}

/* roxygen
@title Return dimensions of a sparse matrix
@param x sparse matrix (any format accepted by `as_SpMat()`)
@return integer vector (2): number of rows and columns
@export
*/
[[cpp4r::register]] SEXP test_sparse_dims(SEXP x) {
  SpMat<double> A = as_SpMat(x);
  writable::integers out(2);
  out[0] = static_cast<int>(A.n_rows);
  out[1] = static_cast<int>(A.n_cols);
  return out;
}

#endif  // ARMADILLO4R_SPARSE
