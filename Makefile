clean:
	@Rscript -e 'devtools::clean_dll("armadillo4rtest"); cpp4r::register("armadillo4rtest")'

install:
	@Rscript -e 'devtools::clean_dll("armadillo4rtest"); devtools::install()'

docs:
	@Rscript -e 'devtools::document(); pkgsite::build_site()'

test:
	@clear
	@echo "==============================="
	@echo "Testing R code"
	@Rscript -e 'devtools::document(); devtools::test(); devtools::install()'
	@echo "==============================="
	@/bin/bash -euo pipefail -c './scripts/test_loop.sh'

check:
	@clear
	@echo "==============================="
	@echo "Checking R code"
	@Rscript -e 'devtools::install(); devtools::check(error_on = "error")'
	@clear
	@echo "==============================="
	@echo "Checking C++ code"
	@export -p USE_CLANG; /bin/bash -euo pipefail -c './scripts/check_loop.sh'
	@echo "==============================="

clang_format=`which clang-format-18`

format: inst/include/armadillo4r.hpp inst/include/armadillo4r/wrappers/*.hpp armadillo4rtest/src/*.cpp
	@${clang_format} -i $^
