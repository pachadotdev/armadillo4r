
<!-- README.md is generated from README.Rmd. Please edit that file -->

# armadillo4r

<!-- badges: start -->

[![Lifecycle:
stable](https://img.shields.io/badge/lifecycle-stable-brightgreen.svg)](https://lifecycle.r-lib.org/articles/stages.html#stable)
[![R-CMD-check](https://github.com/pachadotdev/armadillo4r/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/pachadotdev/armadillo4r/actions/workflows/R-CMD-check.yaml)
[![CRAN
status](https://www.r-pkg.org/badges/version/armadillo4r)](https://CRAN.R-project.org/package=armadillo4r)
[![Test
coverage](https://raw.githubusercontent.com/pachadotdev/armadillo4r/coverage/badges/coverage.svg)](https://github.com/pachadotdev/armadillo4r/actions/workflows/test-coverage.yaml)
[![BuyMeACoffee](https://raw.githubusercontent.com/pachadotdev/buymeacoffee-badges/main/bmc-yellow.svg)](https://buymeacoffee.com/pacha)
<!-- badges: end -->

## About

The goal of armadillo4r is to provide a novel approach to use the
[Armadillo C++ library](https://arma.sourceforge.net/docs.html) by using
the header-only cpp4r R package and to simplify things for the end-user.
It uses the Apache 2.0 license.

⚠️Important⚠️: armadillo4r was created to ease writing functions in your
own packages and does not offer on-the-fly compilation for code
snippets.

The idea is to pass matrices/vectors from R to C++, write pure
C++/Armadillo code for the computation, and then export the result back
to R with the proper data structures.

[RcppArmadillo](https://cran.r-project.org/package=RcppArmadillo) is a
popular R package used by over 1200 CRAN packages as of 2024-12-13.
RcppArmadillo uses the GPL-3 license.

armadillo4r has different internals, even when the shared goal is to use
Armadillo functions from R, and it aims to:

- Enforcing copy-on-write semantics.
- Improving the safety of using the R API from C++ code.
- Using UTF-8 strings everywhere.
- Applying newer C++11 features.
- Having a more straightforward, simpler implementation.
- Faster compilation time with lower memory requirements.
- Growing vectors more efficiently.

The design differences result in marginally higher speed for
armadillo4r, and the real difference for the end user is that
armadillo4r:

- Has a smaller memory footprint.
- Uses the Apache license instead of GPL-3 (i.e., The Apache license is
  permissive and allows commercial use with attribution, unlike the
  GPL-3, which requires open-source redistribution.)
- Can be vendored to be used in restricted environments (i.e., servers
  with no internet access or where IT restricts the installation of
  packages).

A previous package, cpp11armadillo, expands on these details

**[cpp11armadillo: An R package to use the Armadillo C++
library](https://dx.doi.org/10.1016/j.softx.2025.102087).**

If this software is useful to you, please consider donating on [Buy Me A
Coffee](https://buymeacoffee.com/pacha). All donations will be used to
continue improving armadillo4r.

## Getting Started

Install the released version of armadillo4r from CRAN:

``` r
install.packages("armadillo4r")
```

Or, alternatively, install the development version of armadillo4r from
GitHub:

``` r
remotes::install_github("pachadotdev/armadillo4r")
```

## Examples

I have provided a package template for RStudio that also works with VS
Code.

The idea of this package is to be as simple as possible, with the least
amount of setup to get you started.

From RStudio/VSCode, go to an empty directory of your choice and run:

``` r
# subdir + package name
# subdir can be "." to create the package in the current directory
armadillo4r::pkg_template("pkgtemplate", "myownpackage")
```

Then follow the instructions from README.md in the path where the new
package is. The template contains a simple Ordinary Least Squares (OLS)
example that you can run to test the package.

The vignette expands on the OLS estimator, and the [hansen
package](https://pacha.dev/hansen/) expands on how to use armadillo4r
for Econometric models.

The
[armadillo4rtest](https://github.com/pachadotdev/armadillo4r/tree/main/extended-tests/armadillo4rtest)
directory contains a package that I use to test armadillo4r. It includes
tests for OLS, eigenvalues, matrix decompositions (Cholesky and QR), the
Capital Asset Pricing Model (CAPM), and data consistency between R and
C++. Please note that armadillo4rtest is a dummy package to test the C++
build with GitHub Actions, and you do not need to install it. You can
check its code to get extra examples.

## Linear Algebra Libraries

Armadillo supports OpenBLAS, Intel MKL, and the Accelerate framework
(Mac).

Install OpenBLAS on Debian-based systems with:

``` bash
sudo apt-get install libopenblas-dev
```

Restart R and run the following command to verify:

``` r
sessionInfo()
```

R should display something like:

``` r
Matrix products: default
BLAS:   /usr/lib/x86_64-linux-gnu/openblas-pthread/libblas.so.3 
LAPACK: /usr/lib/x86_64-linux-gnu/openblas-pthread/libopenblasp-r0.3.20.so; LAPACK version 3.10.0
```
