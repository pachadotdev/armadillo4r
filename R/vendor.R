#' @title Vendor the cpp4r and armadillo4r headers
#'
#' @description Vendoring is the act of making your own copy of the 3rd party packages your
#' project is using. It is often used in the go language community.
#'
#' This function vendors armadillo4r into your package by copying the armadillo4r
#' headers into the `inst/include` folder of your package and adding
#' 'armadillo4r version: XYZ' to the top of the files, where XYZ is the version of
#' armadillo4r currently installed on your machine.
#'
#' **Note**: vendoring places the responsibility of updating the code on
#' **you**. Bugfixes and new features in armadillo4r will not be available for your
#' code until you run `cpp_vendor()` again.
#'
#' @param path The directory with the vendored headers. It is recommended to use `"./src/vendor"`.
#' The default is `NULL`.
#' @return The path to the vendored code (invisibly).
#' @export
#' @examples
#' # create a new directory
#' dir <- paste0(tempdir(), "/", gsub("\\s+|[[:punct:]]", "", Sys.time()))
#' dir.create(dir, recursive = TRUE)
#'
#' # vendor the armadillo4r headers into the directory
#' vendor(dir)
#' 
#' # just a preview as Armadillo has over 100 files
#' head(list.files(dir, recursive = TRUE))
#'
#' # cleanup
#' unlink(dir, recursive = TRUE)
vendor <- function(path = NULL) {
  if (is.null(path)) {
    stop("You must provide a path to vendor the code into", call. = FALSE)
  }

  # Vendor cpp4r ----

  cpp4r::vendor(path)

  # Vendor armadillo4r ----

  path2 <- file.path(path, "armadillo4r")
  if (dir.exists(path2)) {
    stop("'", path2, "' already exists\n * run unlink('", path2, "', recursive = TRUE)", call. = FALSE)
  }

  dir.create(
    path2,
    recursive = TRUE,
    showWarnings = FALSE
  )

  current_armadillo4r <- system.file(
    "include",
    "armadillo4r",
    package = "armadillo4r"
  )

  if (!nzchar(current_armadillo4r)) {
    stop("armadillo4r is not installed", call. = FALSE)
  }

  armadillo4r_version <- utils::packageVersion("armadillo4r")

  writeLines(
    sprintf(
      "armadillo4r version: %s\nvendored on: %s",
      armadillo4r_version,
      Sys.Date()
    ),
    file.path(path2, "00-armadillo4r-vendoring-info.txt")
  )

  file.copy(
    system.file("include", "armadillo4r.hpp", package = "armadillo4r"),
    file.path(path, "armadillo4r.hpp"),
    overwrite = TRUE
  )

  armadillo4r_files <- list.files(current_armadillo4r, full.names = TRUE)

  file.copy(
    armadillo4r_files,
    path2,
    overwrite = TRUE,
    recursive = TRUE
  )

  if (is_interactive()) {
    message("Vendored armadillo4r to '", path, "'")

    message(paste(
      "Makevars.in and/or Makevars.win should have a line such as",
      "'PKG_CPPFLAGS = -I vendor/' (default) or 'PKG_CPPFLAGS = -I ../inst/include/'"
    ))

    message("DESCRIPTION should not link to armadillo4r or armadillo4r (e.g., 'LinkingTo: armadillo4r, armadillo4r') or the build will ignore the vendored code")
  }

  invisible(path)
}
