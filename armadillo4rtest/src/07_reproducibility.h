/* roxygen
@title Random integer matrix using R's RNG
@param n integer scalar; number of rows and columns
@return integer matrix (N*N) with values in the range 0 to 9
@export
*/
[[cpp4r::register]] integers_matrix<> random_matrix_nxn(const int& n) {
  GetRNGstate();  // Ensure R's RNG state is synchronized
  arma::Mat<int> y(n, n);
  ::arma_rng::randi<int>::fill(y.memptr(), y.n_elem, 0, 9);
  PutRNGstate();  // Ensure R's RNG state is synchronized
  return as_integers_matrix(y);
}
