#pragma once

using namespace arma;
using namespace cpp4r;

#ifndef FIELDS_HPP
#define FIELDS_HPP

////////////////////////////////////////////////////////////////
// R to Armadillo
////////////////////////////////////////////////////////////////

// Convert a cpp4r list of doubles_matrix<> to field<mat>
// Unlike Cube, matrices may have different dimensions.

inline field<mat> as_field_mat(const list& x) {
  const size_t n = x.size();

  if (n == 0) {
    throw std::runtime_error("Cannot convert empty list to field<mat>");
  }

  field<mat> F(n);

  for (size_t i = 0; i < n; ++i) {
    doubles_matrix<> m = x[i];
    const size_t nr = m.nrow();
    const size_t nc = m.ncol();
    // Construct mat directly from R pointer with copy=true
    // This is 1 copy vs the previous 2 (temp alloc + memcpy + assign)
    F(i) = mat(REAL(m.data()), nr, nc, true, false);
  }

  return F;
}

// Convert a cpp4r list of integers_matrix<> to field<imat>

inline field<imat> as_field_imat(const list& x) {
  const size_t n = x.size();

  if (n == 0) {
    throw std::runtime_error("Cannot convert empty list to field<imat>");
  }

  field<imat> F(n);

  for (size_t i = 0; i < n; ++i) {
    integers_matrix<> m = x[i];
    const size_t nr = m.nrow();
    const size_t nc = m.ncol();
    const size_t nm = nr * nc;
    // imat uses sword, R uses int - need conversion
    imat A(nr, nc);
    const int* src = INTEGER(m.data());
    sword* dst = A.memptr();
    for (size_t k = 0; k < nm; ++k) {
      dst[k] = static_cast<sword>(src[k]);
    }
    F(i) = std::move(A);
  }

  return F;
}

// Convert a cpp4r list of doubles to field<vec>

inline field<vec> as_field_vec(const list& x) {
  const size_t n = x.size();

  if (n == 0) {
    throw std::runtime_error("Cannot convert empty list to field<vec>");
  }

  field<vec> F(n);

  for (size_t i = 0; i < n; ++i) {
    doubles v = x[i];
    const size_t nv = v.size();
    // Construct vec directly from R pointer with copy=true
    F(i) = vec(REAL(v.data()), nv, true, false);
  }

  return F;
}

// Convert a cpp4r strings to field<std::string>

inline field<std::string> as_field_str(const strings& x) {
  const size_t n = x.size();

  field<std::string> F(n);

  for (size_t i = 0; i < n; ++i) {
    F(i) = std::string(x[i]);
  }

  return F;
}

////////////////////////////////////////////////////////////////
// Armadillo to R
////////////////////////////////////////////////////////////////

// Convert field<mat> to a cpp4r list of doubles_matrix<>

inline list as_doubles_matrix_field(const field<mat>& F) {
  const size_t n = F.n_elem;

  writable::list out(n);

  for (size_t i = 0; i < n; ++i) {
    const mat& A = F(i);
    const size_t nr = A.n_rows;
    const size_t nc = A.n_cols;
    writable::doubles_matrix<> m(nr, nc);
    std::memcpy(REAL(m), A.memptr(), nr * nc * sizeof(double));
    out[i] = m;
  }

  return out;
}

// Convert field<imat> to a cpp4r list of integers_matrix<>

inline list as_integers_matrix_field(const field<imat>& F) {
  const size_t n = F.n_elem;

  writable::list out(n);

  for (size_t i = 0; i < n; ++i) {
    const imat& A = F(i);
    const size_t nr = A.n_rows;
    const size_t nc = A.n_cols;
    const size_t nm = nr * nc;
    writable::integers_matrix<> m(nr, nc);
    const sword* src = A.memptr();
    int* dst = INTEGER(m);
    for (size_t k = 0; k < nm; ++k) {
      dst[k] = static_cast<int>(src[k]);
    }
    out[i] = m;
  }

  return out;
}

// Convert field<vec> to a cpp4r list of doubles

inline list as_doubles_field(const field<vec>& F) {
  const size_t n = F.n_elem;

  writable::list out(n);

  for (size_t i = 0; i < n; ++i) {
    const vec& a = F(i);
    const size_t nv = a.n_elem;
    writable::doubles v(nv);
    std::memcpy(REAL(v), a.memptr(), nv * sizeof(double));
    out[i] = v;
  }

  return out;
}

// Convert field<std::string> to a cpp4r strings

inline strings as_strings_field(const field<std::string>& F) {
  const size_t n = F.n_elem;

  writable::strings out(n);

  for (size_t i = 0; i < n; ++i) {
    out[i] = F(i);
  }

  return out;
}

#endif
