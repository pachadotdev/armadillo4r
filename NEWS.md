# armadillo4r 1.1.0

* Using Armadillo 15.4.2.
* I am now using `litedown` and `tinyroxygen` for the documentation.

# armadillo4r 1.0.0

* Fully documented vignettes covering over 400 examples.

# armadillo4r 0.9.0

* Using Armadillo 15.2.6
* `as_SpMat()` now accepts any sparse matrix class from the `Matrix` package, including `RsparseMatrix`
  and `TsparseMatrix` subclasses, symmetric (`dsCMatrix`), and unit-triangular (`dtCMatrix`) matrices,
  which are expanded to general form on conversion to `SpMat<double>`.
* `as_SpMat()` and `as_dgCMatrix()` now use the `Matrix` package's public C API (CHOLMOD bridge)
  instead of reading S4 slots directly. The bridge is auto-enabled when the `Matrix` package's
  headers are visible at compile time, which happens when the consuming package declares
  `LinkingTo: Matrix (>= 1.6-2)` in its own DESCRIPTION. Packages that do not need the
  sparse-Matrix bridge no longer have to depend on `Matrix`. The auto-detection can be
  overridden with `-DARMADILLO4R_USE_MATRIX` or `-DARMADILLO4R_NO_MATRIX`.

# armadillo4r 0.8.0

* Adds templates to simplify cube/field data copying between R and Armadillo.
* Adds templates to pass lazy `Glue<>` and `Base<>` expressions to `as_{{ R_TYPE }}()`.

# armadillo4r 0.7.1

* Minor update to the package template to reflect some changes to cpp4r.

# armadillo4r 0.7.0

* Using Armadillo 15.2.1 (Medium Roast Deluxe) thanks to @conradsnicta update notification.
* Improve complex vectors/matrices copying performance by using `memcpy` instead of element-wise copying.
* Explicit testing with Clang and GCC compiler using C++ 14, 17, 20, and 23 standards (Armadillo 15.2.1 
  requires at least C++14)
  
# armadillo4r 0.6.0

* cpp11armadillo was renamed to armadillo4r to reflect its purpose better
* supports copying complex numbers between R and C++
