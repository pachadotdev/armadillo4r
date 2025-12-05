#!/usr/bin/env bash
set -euo pipefail

std=${1:-CXX14}
std=$(echo "$std" | tr '[:lower:]' '[:upper:]')
compiler=${2:-gcc}

echo "==============================="
echo "Preparing C++ code with $std standard and $compiler compiler"
echo ""

# Ensure configure is executable
chmod +x ./extended-tests/armadillo4rtest/configure
chmod +x ./extended-tests/armadillo4rtest/cleanup
