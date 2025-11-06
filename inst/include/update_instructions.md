After updating Armadillo version:

1. `armadillo.hpp` includes a custom `r_messages.hpp` in line 28.
2. `armadillo/arma_forward.hpp` omits `std::cerr` in line 19.
3. `armadillo/config.hpp` calls a custom error redirection in line 229.
