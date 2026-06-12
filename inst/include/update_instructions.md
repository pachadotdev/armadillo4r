Delete `inst/include/armadillo4r/armadillo/` and
`inst/include/armadillo4r/armadillo.hpp`

Replace with the files from `armadillo.x.y.z.tar.xz`:

* `include/armadillo_bits` -> rename to `armadillo`
* `include/armadillo` -> rename to `armadillo.hpp`

After updating Armadillo version:

In `armadillo.hpp`, before `#include "armadillo/config.hpp"`, add:

```cpp
#include "r_messages.hpp"
#define ARMA_COUT_STREAM messagestream()
#define ARMA_CERR_STREAM stopstream()
```
