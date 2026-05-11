#!/usr/bin/env bash
set -euo pipefail

# Accept std as first arg, default to CXX20
std=${1:-CXX20}
std=$(echo "$std" | tr '[:lower:]' '[:upper:]')
compiler=${2:-gcc}

echo "Restoring files for $std and $compiler"

# Convert std to C++ format for DESCRIPTION (e.g., CXX20 -> C++20)
if [ "$std" = "CXX14" ]; then cpp_std="C++14"
elif [ "$std" = "CXX17" ]; then cpp_std="C++17"
elif [ "$std" = "CXX20" ]; then cpp_std="C++20"
elif [ "$std" = "CXX23" ]; then cpp_std="C++23"
else cpp_std="$std"; fi

# Remove generated Makevars
rm -f "./armadillo4rtest/src/Makevars"

# Restore GCC by unsetting USE_CLANG
unset USE_CLANG || true

# Clear check files
rm -rf ./armadillo4rtest.Rcheck || true
