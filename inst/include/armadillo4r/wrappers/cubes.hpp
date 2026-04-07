#pragma once

using namespace arma;
using namespace cpp4r;

#ifndef CUBES_HPP
#define CUBES_HPP

////////////////////////////////////////////////////////////////
// R to Armadillo
////////////////////////////////////////////////////////////////

// Convert a cpp4r list of doubles_matrix<> to Cube<double>
// All matrices in the list must have the same dimensions.

// Helper for list_to_Cube_ to get dimensions (doubles specialization)
template <typename T>
inline void list_get_dims_(const list& x, size_t& n_rows, size_t& n_cols,
                          typename std::enable_if<std::is_same<T, double>::value>::type* = 0) {
  doubles_matrix<> first = x[0];
  n_rows = first.nrow();
  n_cols = first.ncol();
}

// Helper for list_to_Cube_ to get dimensions (integers specialization)
template <typename T>
inline void list_get_dims_(const list& x, size_t& n_rows, size_t& n_cols,
                          typename std::enable_if<!std::is_same<T, double>::value>::type* = 0) {
  integers_matrix<> first = x[0];
  n_rows = first.nrow();
  n_cols = first.ncol();
}

// Helper: copy slice for double type
template <typename T>
inline void list_copy_slice_(const list& x, Cube<T>& C, size_t s, size_t n_rows,
                            size_t n_cols, size_t slice_size,
                            typename std::enable_if<std::is_same<T, double>::value>::type* = 0) {
  doubles_matrix<> m = x[s];
  if (static_cast<size_t>(m.nrow()) != n_rows ||
      static_cast<size_t>(m.ncol()) != n_cols) {
    throw std::runtime_error(
        "All matrices in the list must have the same dimensions to form a Cube");
  }
  std::memcpy(C.slice(s).memptr(), REAL(m.data()), slice_size * sizeof(double));
}

// Helper: copy slice for non-double types
template <typename T>
inline void list_copy_slice_(const list& x, Cube<T>& C, size_t s, size_t n_rows,
                            size_t n_cols, size_t slice_size,
                            typename std::enable_if<!std::is_same<T, double>::value>::type* = 0) {
  integers_matrix<> m = x[s];
  if (static_cast<size_t>(m.nrow()) != n_rows ||
      static_cast<size_t>(m.ncol()) != n_cols) {
    throw std::runtime_error(
        "All matrices in the list must have the same dimensions to form a Cube");
  }
  const int* src = INTEGER(m.data());
  T* dst = C.slice(s).memptr();
  for (size_t idx = 0; idx < slice_size; ++idx) {
    dst[idx] = static_cast<T>(src[idx]);
  }
}

template <typename T>
inline Cube<T> list_to_Cube_(const list& x) {
  const size_t n_slices = x.size();

  if (n_slices == 0) {
    throw std::runtime_error("Cannot convert empty list to Cube");
  }

  // Determine dimensions from the first element using SFINAE helper
  size_t n_rows, n_cols;
  list_get_dims_<T>(x, n_rows, n_cols);

  Cube<T> C(n_rows, n_cols, n_slices);
  const size_t slice_size = n_rows * n_cols;

  for (size_t s = 0; s < n_slices; ++s) {
    list_copy_slice_<T>(x, C, s, n_rows, n_cols, slice_size);
  }

  return C;
}

inline Cube<double> as_Cube(const list& x) { return list_to_Cube_<double>(x); }

inline Cube<int> as_icube(const list& x) { return list_to_Cube_<int>(x); }

// Lowercase aliases

inline Cube<double> as_cube(const list& x) { return as_Cube(x); }

////////////////////////////////////////////////////////////////
// Armadillo to R
////////////////////////////////////////////////////////////////

// Convert Cube<double> to a cpp4r list of doubles_matrix<>

// Helper: convert cube slice to R matrix (doubles specialization)
template <typename T, typename MatRType>
inline void cube_slice_to_r_(writable::list& out, const Cube<T>& C, size_t s,
                            size_t n_rows, size_t n_cols, size_t slice_size,
                            typename std::enable_if<std::is_same<MatRType, doubles_matrix<>>::value>::type* = 0) {
  writable::doubles_matrix<> m(n_rows, n_cols);
  std::memcpy(REAL(m), C.slice(s).memptr(), slice_size * sizeof(double));
  out[s] = m;
}

// Helper: convert cube slice to R matrix (integers specialization)
template <typename T, typename MatRType>
inline void cube_slice_to_r_(writable::list& out, const Cube<T>& C, size_t s,
                            size_t n_rows, size_t n_cols, size_t slice_size,
                            typename std::enable_if<!std::is_same<MatRType, doubles_matrix<>>::value>::type* = 0) {
  writable::integers_matrix<> m(n_rows, n_cols);
  const T* src = C.slice(s).memptr();
  int* dst = INTEGER(m);
  for (size_t idx = 0; idx < slice_size; ++idx) {
    dst[idx] = static_cast<int>(src[idx]);
  }
  out[s] = m;
}

template <typename T, typename MatRType>
inline list Cube_to_list_(const Cube<T>& C) {
  const size_t n_slices = C.n_slices;
  const size_t n_rows = C.n_rows;
  const size_t n_cols = C.n_cols;
  const size_t slice_size = n_rows * n_cols;

  writable::list out(static_cast<R_xlen_t>(n_slices));

  for (size_t s = 0; s < n_slices; ++s) {
    cube_slice_to_r_<T, MatRType>(out, C, s, n_rows, n_cols, slice_size);
  }

  return out;
}

inline list as_doubles_matrix_list(const Cube<double>& C) {
  return Cube_to_list_<double, doubles_matrix<>>(C);
}

inline list as_integers_matrix_list(const Cube<int>& C) {
  return Cube_to_list_<int, integers_matrix<>>(C);
}

inline list as_integers_matrix_list(const Cube<unsigned int>& C) {
  return Cube_to_list_<unsigned int, integers_matrix<>>(C);
}

inline list as_integers_matrix_list(const ucube& C) {
  return Cube_to_list_<uword, integers_matrix<>>(C);
}

inline list as_integers_matrix_list(const icube& C) {
  return Cube_to_list_<sword, integers_matrix<>>(C);
}

#endif
