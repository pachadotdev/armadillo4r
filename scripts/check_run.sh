#!/usr/bin/env bash
set -euo pipefail

# Export USE_CLANG for R subprocesses if it's set
if [ -n "${USE_CLANG:-}" ]; then
  export USE_CLANG
fi

# Accept std and compiler from positional args or environment; avoid unbound var with set -u
# Priority: positional args > existing environment variables > safe defaults
std="${1:-${std:-CXX14}}"
compiler="${2:-${compiler:-gcc}}"

# Run the bench script (will exit on error)
Rscript -e 'cpp4r::register("armadillo4rtest")'
Rscript -e 'devtools::document("armadillo4rtest")'
LOG="devtools-check-${std}-${compiler}.log"

# Build package tarball first (devtools::build returns path)
TARBALL=$(Rscript -e 'cat(devtools::build("armadillo4rtest", quiet = TRUE))' 2>/dev/null)
if [ -z "${TARBALL}" ]; then
	echo "Failed to build tarball for armadillo4rtest."
	exit 1
fi

# Run R CMD check on the tarball and capture output. Skip PDF/manual to avoid TeX font issues.
R CMD check --as-cran --no-manual "${TARBALL}" &> "${LOG}" || true

# Inspect log for ERRORs only. Allow WARNINGs and NOTEs.
if grep -q "\bERROR\b" "${LOG}"; then
	echo "R CMD check found ERRORs. See ${LOG} for details."
	# Print a short excerpt for convenience
	grep -n "\bERROR\b" -n "${LOG}" || true
	exit 1
else
	echo "R CMD check completed with no ERRORs. Warnings/Notes (if any) are allowed. See ${LOG} for full output."
fi

rm -f "${TARBALL}"

echo "Run complete."
