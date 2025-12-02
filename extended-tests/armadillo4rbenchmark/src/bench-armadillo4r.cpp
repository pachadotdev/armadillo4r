#include <armadillo4r.hpp>
#include <cpp4r.hpp>
#include <cstring>
#include <vector>

using namespace cpp4r;
using namespace arma;

/* roxygen
@title Add Two Matrices
@export
*/
[[cpp4r::register]] doubles_matrix<> add_two_cpp4r(const doubles_matrix<>& a,
                                                   const doubles_matrix<>& b) {
  mat A = as_mat(a);
  mat B = as_mat(b);

  mat Z = A + B;

  return as_doubles_matrix(Z);
}

/* roxygen
@title Add Four Matrices
@export
*/
[[cpp4r::register]] doubles_matrix<> add_four_cpp4r(const doubles_matrix<>& a,
                                                    const doubles_matrix<>& b,
                                                    const doubles_matrix<>& c,
                                                    const doubles_matrix<>& d) {
  mat A = as_mat(a);
  mat B = as_mat(b);
  mat C = as_mat(c);
  mat D = as_mat(d);

  mat Z = A + B + C + D;

  return as_doubles_matrix(Z);
}

/* roxygen
@title Multiply Four Matrices
@export
*/
[[cpp4r::register]] doubles_matrix<> multiply_four_cpp4r(const doubles_matrix<>& a,
                                                         const doubles_matrix<>& b,
                                                         const doubles_matrix<>& c,
                                                         const doubles_matrix<>& d) {
  mat A = as_mat(a);
  mat B = as_mat(b);
  mat C = as_mat(c);
  mat D = as_mat(d);

  uword n = A.n_cols;
  uword n5 = n / 5;
  uword n10 = n / 10;
  uword n15 = n / 15;
  uword n20 = n / 20;

  mat Z = A.submat(0, 0, n5 - 1, n5 - 1) * B.submat(0, 0, n5 - 1, n10 - 1) *
          C.submat(0, 0, n10 - 1, n15 - 1) * D.submat(0, 0, n15 - 1, n20 - 1);

  return as_doubles_matrix(Z);
}

/* roxygen
@title Submatrix Manipulation
@export
*/
[[cpp4r::register]] doubles_matrix<> submatrix_manipulation_cpp4r(
    const doubles_matrix<>& a, const doubles_matrix<>& b) {
  mat A = as_mat(a);
  mat B = as_mat(b);

  mat Z = B;
  Z.row(Z.n_rows - 1) = A.row(0);

  return as_doubles_matrix(Z);
}

/* roxygen
@title Multi-Operation Expression
@export
*/
[[cpp4r::register]] double multi_operation_cpp4r(const doubles_matrix<>& a,
                                                 const doubles_matrix<>& b,
                                                 const doubles_matrix<>& c) {
  mat A = as_mat(a);
  mat B = as_mat(b);
  mat C = as_mat(c);

  // Compute: t(A.col(0)) * inv(diagmat(B)) * C.col(0)
  // This is equivalent to: sum(A[i,0] * (1/B[i,i]) * C[i,0]) for i in 0..n-1
  vec a_col = A.col(0);
  vec b_diag = B.diag();
  vec c_col = C.col(0);

  double Z = as_scalar(a_col.t() * (c_col / b_diag));

  return Z;
}
