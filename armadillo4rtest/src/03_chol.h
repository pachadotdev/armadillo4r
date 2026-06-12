/* roxygen
@title Cholesky decomposition
@param x symmetric positive definite numeric matrix (N*N)
@param type decomposition type: `"upper"` for upper triangular or `"lower"`
  for lower triangular
@return triangular factor matrix (N*N)
@export
*/
[[cpp4r::register]] doubles_matrix<> chol_mat(const doubles_matrix<>& x,
                                              std::string type) {
  Mat<double> X = as_Mat(x);

  Mat<double> res;

  if (type == "upper") {
    res = chol(X);
  } else if (type == "lower") {
    res = chol(X, "lower");
  } else {
    stop("Invalid type");
  }

  return as_doubles_matrix(res);
}
