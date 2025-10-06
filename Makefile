clean:
	@Rscript -e 'devtools::clean_dll()'
	@Rscript -e 'devtools::clean_dll("armadillo4rtest")'

test:
	@echo "Testing R code"
	@Rscript -e 'devtools::document(); devtools::test(); devtools::install()'
	@echo "Testing C++ code"
	@Rscript -e 'devtools::clean_dll("armadillo4rtest"); devtools::load_all("armadillo4rtest"); devtools::test("armadillo4rtest")'

check:
	@echo "Local"
	@Rscript -e 'devtools::document(); devtools::install()'
	@Rscript -e 'devtools::check(); cpp4r::register("armadillo4rtest"); devtools::check("armadillo4rtest")'

site:
	@Rscript -e 'devtools::document()'
	@Rscript -e 'pkgdown::build_site()'

install:
	@Rscript -e 'devtools::install()'

clang_format=`which clang-format-18`

format: inst/include/armadillo4r.hpp inst/include/armadillo4r/wrappers/*.hpp armadillo4rtest/src/*.cpp
	@${clang_format} -i $^
