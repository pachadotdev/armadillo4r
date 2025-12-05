#!/usr/bin/env bash
set -euo pipefail

std=${1:-CXX14}
std=$(echo "$std" | tr '[:lower:]' '[:upper:]')
compiler=${2:-gcc}

echo "Restoring files for $std with $compiler"

# Convert std to C++ format for DESCRIPTION (e.g., CXX20 -> C++20)
if [ "$std" = "CXX14" ]; then cpp_std="C++14"
elif [ "$std" = "CXX17" ]; then cpp_std="C++17"
elif [ "$std" = "CXX20" ]; then cpp_std="C++20"
elif [ "$std" = "CXX23" ]; then cpp_std="C++23"
else cpp_std="$std"; fi

pkgs=(armadillo4rbenchmark cpp11armadillobenchmark RcppArmadillobenchmark)
for pkg in "${pkgs[@]}"; do
	echo "- Restoring: $pkg"
	if [ -d "./extended-tests/${pkg}/src" ]; then
		mfile="./extended-tests/${pkg}/src/Makevars.in"
		if [ -f "$mfile" ]; then
			# replace existing CXX_STD line (handles optional quotes), otherwise prepend
			if grep -q '^CXX_STD[[:space:]]*=' "$mfile"; then
				sed -E -i 's|^CXX_STD[[:space:]]*=.*|CXX_STD = CXXNN|' "$mfile"
			fi
		fi
		# Remove generated Makevars
		rm -f "./extended-tests/${pkg}/src/Makevars"
	fi
done

# Restore GCC by unsetting USE_CLANG
echo "Unsetting USE_CLANG to restore GCC"
unset USE_CLANG || true
