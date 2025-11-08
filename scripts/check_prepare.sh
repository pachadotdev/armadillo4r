#!/usr/bin/env bash
set -euo pipefail

std=${1:-CXX11}
compiler=${2:-gcc}

echo "==============================="
echo "Preparing C++ code with $std standard and $compiler compiler"
echo ""

# Note: USE_CLANG should be set by the calling script (check_loop.sh)
# and will be read by Makevars during R CMD INSTALL

# update or add CXX_STD in package Makevars.in without clobbering other content
mfile="./armadillo4rtest/src/Makevars.in"
if [ -f "$mfile" ]; then
	# replace existing CXX_STD line, or add it at top if not present
	if grep -q '^CXX_STD[[:space:]]*=' "$mfile"; then
	    sed -E -i "s|^CXX_STD[[:space:]]*=.*|CXX_STD = ${std}|" "$mfile"
	else
	    # preserve original content, prepend new CXX_STD
		tmpfile="${mfile}.tmp"
		printf "CXX_STD = %s\n" "$std" > "$tmpfile"
		cat "$mfile" >> "$tmpfile"
		mv "$tmpfile" "$mfile"
	fi
else
    # file doesn't exist; create minimal Makevars.in with CXX_STD
	echo "CXX_STD = $std" > "$mfile"
fi
