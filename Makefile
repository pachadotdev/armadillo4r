clean:
	@Rscript --vanilla -e 'devtools::clean_dll("armadillo4rtest");'

install:
	@Rscript --vanilla -e 'devtools::install("./")'
	@Rscript --vanilla -e 'armadillo4r::unvendor("./armadillo4rtest/src/vendor"); armadillo4r::vendor("./armadillo4rtest/src/vendor")'

docs:
	@Rscript --vanilla -e 'devtools::document("./"); pkgsite::build_site("./")'

STANDARDS := cxx20
COMPILERS := gcc

define run-check
check-$(1)-$(2):
	@echo "Checking C++ code with $(1) standard and $(2) compiler"
	@$$(MAKE) install
	@if [ "$(2)" = "clang" ]; then export USE_CLANG=1; else unset USE_CLANG; fi; \
	./checks/check_prepare.sh "$(1)" "$(2)"; \
	if ! ./checks/check_run.sh "$(1)" "$(2)"; then \
		echo "Check failed"; \
		./checks/check_restore.sh "$(1)" "$(2)"; \
		exit 1; \
	fi; \
	./checks/check_restore.sh "$(1)" "$(2)"
endef

# Generate all check-STANDARD-COMPILER targets
$(foreach std,$(STANDARDS),$(foreach cc,$(COMPILERS),$(eval $(call run-check,$(std),$(cc)))))

# Run all checks
check: $(foreach std,$(STANDARDS),$(foreach cc,$(COMPILERS),check-$(std)-$(cc)))

# Run checks for a single compiler
check-gcc: $(foreach std,$(STANDARDS),check-$(std)-gcc)
check-clang: $(foreach std,$(STANDARDS),check-$(std)-clang)

clang_format=`which clang-format-18`

format: $(shell find . -name '*.h' ! -path './inst/include/armadillo4r/armadillo/*' ! -path '*/vendor/*') \
        $(shell find . -name '*.hpp' ! -path './inst/include/armadillo4r/armadillo/*' ! -path '*/vendor/*' ! -path './inst/include/armadillo4r/armadillo.hpp') \
        $(shell find . -name '*.cpp' ! -path './inst/include/armadillo4r/armadillo/*' ! -path '*/vendor/*')
	@${clang_format} -i $?
