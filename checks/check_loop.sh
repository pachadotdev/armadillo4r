#!/usr/bin/env bash
set -euo pipefail

rm -f ./checks/check-results.md

for std in CXX23 CXX20 CXX17 CXX14; do
  for compiler in clang gcc; do
    echo "==============================="
    echo "Checking C++ code with $std standard and $compiler compiler"

    # Set USE_CLANG environment variable for this iteration
    if [ "$compiler" = "clang" ]; then
      export USE_CLANG=1
    else
      unset USE_CLANG || true
    fi

    ./checks/check_prepare.sh "$std" "$compiler"

    touch ./checks/check-results.md
    
    # Run check, but don't exit on failure
    # Pass the current loop's std and compiler so `check_run.sh` can create
    # a per-iteration LOG file (avoids overwriting the previous run's log).
    if ! ./checks/check_run.sh "$std" "$compiler"; then
      echo "WARNING: check_run.sh failed for $std standard with $compiler, continuing..."
      echo "$std + $compiler = fail" >> ./check-results.md || true
    else 
      echo "$std + $compiler = ok" >> ./check-results.md || true
    fi

    ./checks/check_restore.sh "$std" "$compiler"

    echo "==============================="
    echo ""
  done
done
