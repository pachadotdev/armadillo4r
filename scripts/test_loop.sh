#!/usr/bin/env bash
set -euo pipefail

# Armadillo 15.2.1 deprecated C++11 support, so we start from C++14

for std in CXX14 CXX17 CXX20 CXX23; do
  echo " "
  echo "==============================="
  echo "Testing C++ code with $std standard"
  echo "CXX_STD = $std" > ./armadillo4rtest/src/Makevars.in

  if [ "$std" = "CXX11" ]; then cpp_std="C++11"
  elif [ "$std" = "CXX14" ]; then cpp_std="C++14"
  elif [ "$std" = "CXX17" ]; then cpp_std="C++17"
  elif [ "$std" = "CXX20" ]; then cpp_std="C++20"
  elif [ "$std" = "CXX23" ]; then cpp_std="C++23"
  else cpp_std="$std"; fi

  sed -i "s/C++NN/${cpp_std}/" ./armadillo4rtest/DESCRIPTION
  echo "CXX_STD = $std" > ./armadillo4rtest/src/Makevars.in

  Rscript -e 'devtools::clean_dll("armadillo4rtest"); armadillo4r::register("armadillo4rtest"); devtools::document("armadillo4rtest");'
  Rscript -e 'devtools::load_all("armadillo4rtest"); devtools::test("armadillo4rtest")'

  sed -i "s/${std}/C++NN/" ./armadillo4rtest/DESCRIPTION || true
  echo "" > ./armadillo4rtest/src/Makevars.in

  echo "==============================="
done
