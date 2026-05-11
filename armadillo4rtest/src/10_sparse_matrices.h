#ifndef ARMADILLO4R_NO_SPARSE

[[cpp4r::register]] SEXP test_dgCMatrix_to_SpMat(SEXP x) {
  // Convert from dgCMatrix to SpMat
  SpMat<double> A = as_SpMat(x);

  // Optional: perform some operation on A
  // For example, multiply each element by 2
  A *= 1.0;

  // Convert back to dgCMatrix and return
  return as_dgCMatrix(A);
}

[[cpp4r::register]] SEXP test_sparse_to_dgCMatrix(SEXP x) {
  // Accepts any sparse Matrix object (CsparseMatrix, RsparseMatrix,
  // TsparseMatrix, symmetric, triangular, ...) and round-trips it as a
  // dgCMatrix.
  SpMat<double> A = as_SpMat(x);
  return as_dgCMatrix(A);
}

[[cpp4r::register]] SEXP test_sparse_dims(SEXP x) {
  SpMat<double> A = as_SpMat(x);
  writable::integers out(2);
  out[0] = static_cast<int>(A.n_rows);
  out[1] = static_cast<int>(A.n_cols);
  return out;
}

#endif  // ARMADILLO4R_NO_SPARSE
