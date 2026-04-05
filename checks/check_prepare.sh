#!/usr/bin/env bash
set -euo pipefail

std=${1:-CXX14}
std=$(echo "$std" | tr '[:lower:]' '[:upper:]')
compiler=${2:-gcc}

echo "==============================="
echo "Preparing C++ code with $std standard and $compiler compiler"
echo ""

# Ensure configure is executable
chmod +x ./armadillo4rtest/configure
chmod +x ./armadillo4rtest/cleanup
