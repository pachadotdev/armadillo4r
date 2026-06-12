/* roxygen
@title Matrix arithmetic demo
@param a numeric matrix
@return numeric matrix combining scalar addition, matrix addition and
  multiplication, and element-wise multiplication
@export
*/
[[cpp4r::register]] doubles_matrix<> matrix1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  double x = A(0, 0);  // access an element on row 1, column 1
  A = A + x;           // scalar addition

  mat B = A + A;  // matrix addition
  mat C = A * B;  // matrix multiplication
  mat D = A % B;  // element-wise matrix multiplication

  mat res = B + C + D;

  return as_doubles_matrix(res);  // convert from C++ to R
}

/* roxygen
@title Complex matrix construction demo
@param a numeric matrix used as real part
@return complex matrix constructed from two real matrices
@export
*/
[[cpp4r::register]] complexes_matrix<> matrix2_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);
  mat B = A + A;

  cx_mat X(A, B);  // construct a complex matrix out of two real matrices

  B.zeros();                       // set all elements to zero
  B.set_size(A.n_rows, A.n_cols);  // resize the matrix
  B.ones(5, 6);                    // same as mat B(5, 6, fill::ones)

  mat::fixed<5, 6> F;  // fixed size matrix

  double aux_mem[24] = {};          // auxiliary memory (zero-initialized)
  mat H(&aux_mem[0], 4, 6, false);  // use auxiliary memory

  X = X + F.submat(0, 0, 1, 1) + H(1, 2);

  // list of matrices output

  // Mat<double> res_real = real(X);
  // Mat<double> res_imag = imag(X);

  // writable::list res;
  // res.push_back({"real"_nm = as_doubles_matrix(res_real)});
  // res.push_back({"imag"_nm = as_doubles_matrix(res_imag)});

  // return res;

  // matrix output

  return as_complexes_matrix(X);
}

/* roxygen
@title Column vector extraction demo
@param x numeric vector (length 10)
@param y numeric vector (length 10)
@return numeric vector: column 6 of a random 10*10 matrix plus `y` plus `x`
@export
*/
[[cpp4r::register]] doubles column1_(const doubles& x, const doubles& y) {
  vec X = as_Col(x);  // convert from R to C++
  vec Y = as_Col(y);

  mat A(10, 10, fill::randu);
  vec Z = A.col(5);  // extract a column vector

  Z = Z + Y + X;

  return as_doubles(Z);  // convert from C++ to R
}

/* roxygen
@title Row vector extraction demo
@param x numeric vector (length 10)
@param y numeric vector (length 10)
@return numeric vector: row 6 of a random 10*10 matrix plus `y` plus `x`
@export
*/
[[cpp4r::register]] doubles row1_(const doubles& x, const doubles& y) {
  vec X = as_Col(x);  // convert from R to C++
  vec Y = as_Col(y);

  mat A(10, 10, fill::randu);

  rowvec Z = A.row(5);    // extract a row vector
  Z = Z + Y.t() + X.t();  // transpose Y and X to be able to sum

  vec res = Z.t();

  return as_doubles(res);  // convert from C++ to R
}

/* roxygen
@title Cube (3-D array) construction and slice arithmetic demo
@param a numeric matrix (first slice)
@param b numeric matrix (second slice)
@return numeric matrix: sum of first slice of 2*cube plus second slice of
  element-wise cube square
@export
*/
[[cpp4r::register]] doubles_matrix<> cube1_(const doubles_matrix<>& a,
                                            const doubles_matrix<>& b) {
  mat A = as_Mat(a);  // convert from R to C++
  mat B = as_Mat(b);

  cube X(A.n_rows, A.n_cols, 2);  // create a cube with 2 slices
  X.slice(0) = A;                 // copy A into first slice
  X.slice(1) = B;                 // copy B into second slice

  cube Y = X + X;  // cube addition
  cube Z = X % X;  // element-wise cube multiplication

  mat res = Y.slice(0) + Z.slice(1);

  return as_doubles_matrix(res);  // convert from C++ to R
}

/* roxygen
@title Field-of-matrices construction and arithmetic demo
@param a numeric matrix (first field element)
@param b numeric matrix (second field element)
@return numeric matrix: sum of two input matrices plus transpose of their sum
@export
*/
[[cpp4r::register]] doubles_matrix<> field1_(const doubles_matrix<>& a,
                                             const doubles_matrix<>& b) {
  mat A = as_Mat(a);  // convert from R to C++
  mat B = as_Mat(b);

  field<mat> F(A.n_rows, A.n_cols, 3);  // create a field with 2 matrices
  F(0) = A;                             // copy A into first location
  F(1) = B;                             // copy B into second location
  F(2) = F(0) + F(1);                   // matrix addition

  mat res = F(0) + F(1) + F(2).t();

  return as_doubles_matrix(res);  // convert from C++ to R
}

/* roxygen
@title Matrix dimension attributes
@param a numeric matrix
@return named integer vector with elements `n_rows`, `n_cols`, and `n_elem`
@export
*/
[[cpp4r::register]] integers attr1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  // uword or int can be used
  int n_rows = A.n_rows;  // number of rows
  int n_cols = A.n_cols;  // number of columns
  int n_elem = A.n_elem;  // number of elements

  writable::integers res({n_rows, n_cols, n_elem});
  res.attr("names") = strings({"n_rows", "n_cols", "n_elem"});

  return res;
}

/* roxygen
@title Element access and nested-loop mutation demo
@param a numeric matrix
@return numeric matrix with each element increased by element (1,1) of the
  original matrix plus element 2 of a random vector
@export
*/
[[cpp4r::register]] doubles_matrix<> access1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++
  A(1, 1) = 123.0;    // set element at row 2, column 2

  vec B(2, fill::randu);

  double x = A(0, 1);  // copy element at row 1, column 2 to a double
  double y = B(1);     // copy element at coordinate 2 to a double

  uword i, j;  // int also works
  uword N = A.n_rows;
  uword M = A.n_cols;

  for (i = 0; i < N; ++i) {
    for (j = 0; j < M; ++j) {
      A(i, j) = A(i, j) + x + y;
    }
  }

  return as_doubles_matrix(A);  // convert from C++ to R
}

/* roxygen
@title Brace-initializer construction demo
@param a numeric matrix
@return numeric matrix: `a` plus a 2*2 brace-initialized matrix with diagonal
  shifted by a brace-initialized vector
@export
*/
[[cpp4r::register]] doubles_matrix<> initialization1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);         // convert from R to C++
  mat B = {{1, 2}, {3, 4}};  // create new matrix
  vec C = {1, 2};            // create new column vector

  // sum C to the diagonal of A
  A(0, 0) = A(0, 0) + C(0);
  A(1, 1) = A(1, 1) + C(1);

  mat D = A + B;

  return as_doubles_matrix(D);  // convert from C++ to R
}

/* roxygen
@title Matrix zeros fill demo
@param a numeric matrix
@return numeric matrix: sum of three zero-filled matrices of the same size
@export
*/
[[cpp4r::register]] doubles_matrix<> zeros1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++
  A.zeros();          // set all elements to zero

  mat B;
  B.zeros(size(A));  // set size to be the same as A and set all elements to zero

  mat C(A.n_rows, A.n_cols, fill::zeros);

  mat D = A + B + C;

  return as_doubles_matrix(D);  // convert from C++ to R
}

/* roxygen
@title Matrix ones fill demo
@param a numeric matrix
@return numeric matrix: sum of three ones-filled matrices of the same size
@export
*/
[[cpp4r::register]] doubles_matrix<> ones1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++
  A.ones();           // set all elements to zero

  mat B;
  B.ones(size(A));  // set size to be the same as A and set all elements to zero

  mat C(A.n_rows, A.n_cols, fill::ones);

  mat D = A + B + C;

  return as_doubles_matrix(D);  // convert from C++ to R
}

/* roxygen
@title Identity matrix construction demo
@param a numeric matrix
@return numeric matrix: sum of three identity matrices of the same size
@export
*/
[[cpp4r::register]] doubles_matrix<> eye1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++
  A.eye();            // create an identity matrix

  mat B;
  B.eye(size(A));  // another identity matrix

  uword N = A.n_rows;
  uword M = A.n_cols;
  mat C(N, M, fill::randu);
  C.eye(N, M);  // yet another identity matrix

  mat D = A + B + C;

  return as_doubles_matrix(D);  // convert from C++ to R
}

/* roxygen
@title Random uniform matrix fill demo
@param a numeric matrix
@return numeric matrix: `a` plus two random uniform matrices of the same size
@export
*/
[[cpp4r::register]] doubles_matrix<> randu1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  mat B;
  B.randu(size(A));  // random uniform matrix with the same size as A

  mat C(A.n_rows, A.n_cols, fill::randu);

  mat D = A + B + C;

  return as_doubles_matrix(D);  // convert from C++ to R
}

/* roxygen
@title Random normal matrix fill demo
@param a numeric matrix
@return numeric matrix: `a` plus two random normal matrices of the same size
@export
*/
[[cpp4r::register]] doubles_matrix<> randn1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  mat B;
  B.randn(size(A));  // random normal matrix with the same size as A

  mat C(A.n_rows, A.n_cols, fill::randn);

  mat D = A + B + C;

  return as_doubles_matrix(D);  // convert from C++ to R
}

/* roxygen
@title Random uniform matrix using R's RNG
@param n integer scalar; matrix dimension
@return numeric matrix (N*N) with uniform random values
@export
*/
[[cpp4r::register]] doubles_matrix<> randu2_(const int& n) {
  GetRNGstate();  // Ensure R's RNG state is synchronized
  mat y(n, n);
  ::arma_rng::randu<double>::fill(y.memptr(), y.n_elem);
  PutRNGstate();

  return as_doubles_matrix(y);
}

/* roxygen
@title Random normal matrix using R's RNG
@param n integer scalar; matrix dimension
@return numeric matrix (N*N) with standard normal random values
@export
*/
[[cpp4r::register]] doubles_matrix<> randn2_(const int& n) {
  GetRNGstate();  // Ensure R's RNG state is synchronized
  mat y(n, n);
  ::arma_rng::randn<double>::fill(y.memptr(), y.n_elem);
  PutRNGstate();

  return as_doubles_matrix(y);
}

/* roxygen
@title fill::value fill demo
@param a numeric matrix used to determine size
@return numeric matrix: sum of matrices filled with 200, 100, zeros, and ones
@export
*/
[[cpp4r::register]] doubles_matrix<> fill1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  uword N = A.n_rows;
  uword M = A.n_cols;

  mat B(size(A), fill::value(200.0));  // create a matrix filled with 200.0
  mat C(N, M, fill::value(100.0));     // matrix filled with 100.0
  mat D(N, M, fill::zeros);            // matrix filled with zeros
  mat E(N, M, fill::ones);             // matrix filled with ones

  mat F = A + B + C + D + E;

  return as_doubles_matrix(F);  // convert from C++ to R
}

/* roxygen
@title imbue fill via C++ RNG demo
@param a numeric matrix
@return numeric matrix: `a` plus a matrix filled via Mersenne-twister uniform
  distribution
@export
*/
[[cpp4r::register]] doubles_matrix<> imbue1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  std::mt19937 engine;  // Mersenne twister random number engine
  std::uniform_real_distribution<double> distr(0.0, 1.0);

  mat B(size(A), fill::none);                // create an empty matrix
  B.imbue([&]() { return distr(engine); });  // fill with random values

  mat C = A + B;

  return as_doubles_matrix(C);  // convert from C++ to R
}

/* roxygen
@title imbue fill via R's RNG demo
@param a numeric matrix
@return numeric matrix: `a` plus a matrix filled via `unif_rand()`
@export
*/
[[cpp4r::register]] doubles_matrix<> imbue2_(const doubles_matrix<>& a) {
  GetRNGstate();  // Ensure R's RNG state is synchronized

  mat A = as_Mat(a);  // Convert from R to C++

  mat B(size(A), fill::none);             // Create an empty matrix
  B.imbue([]() { return unif_rand(); });  // Fill with random values

  mat C = A + B;

  PutRNGstate();

  return as_doubles_matrix(C);  // Convert from C++ to R
}

/* roxygen
@title clean() small-value zeroing demo
@param n integer scalar; matrix dimension
@return numeric matrix (N*N) with near-zero elements set to zero
@export
*/
[[cpp4r::register]] doubles_matrix<> clean1_(const int& n) {
  mat A(n, n, fill::randu);  // create a random matrix

  A(0, 0) = datum::eps;  // set the diagonal with small values (+/- epsilon)
  A(1, 1) = -datum::eps;

  A.clean(datum::eps);  // set elements with small values to zero

  return as_doubles_matrix(A);  // Convert from C++ to R
}
