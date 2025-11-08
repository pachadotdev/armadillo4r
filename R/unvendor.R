#' Unvendor the armadillo4r headers
#'
#' This function removes the vendored armadillo4r headers from your package by
#' automatically finding the vendored headers.
#'
#' @param path The directory with the vendored headers. It is recommended to use `"./src/vendor"`.
#' The default is `NULL`.
#' @return The path to the unvendored code (invisibly).
#' @export
#' @examples
#' # create a new directory
#' dir <- paste0(tempdir(), "/", gsub("\\s+|[[:punct:]]", "", Sys.time()))
#' dir.create(dir, recursive = TRUE)
#'
#' # vendor the armadillo4r headers into the directory
#' vendor(dir)
#'
#' # unvendor the armadillo4r headers from the directory
#' unvendor(dir)
#'
#' # cleanup
#' unlink(dir, recursive = TRUE)
unvendor <- function(path = NULL) {
  stopifnot(!is.null(path), dir.exists(path))

  # Unvendor cpp4r headers
  cpp4r::unvendor(path)

  # Find the vendoring info file
  info_file <- list.files(path, pattern = "00-armadillo4r-vendoring-info.txt", recursive = TRUE, full.names = TRUE)

  if (length(info_file) == 0L) {
    if (is_interactive()) {
      message("Could not find vendored headers")
    }
    return(invisible(NULL))
  }

  # The info file is in the same level as armadillo4r
  parent_dir <- dirname(info_file)
  armadillo4r_dir <- file.path(parent_dir, "armadillo4r")
  cpp4r_dir <- file.path(parent_dir, "cpp4r")

  unlink(armadillo4r_dir, recursive = TRUE)
  unlink(cpp4r_dir, recursive = TRUE)

  # Remove armadillo4r.hpp from the parent directory
  armadillo4r_hpp_path <- file.path(parent_dir, "armadillo4r.hpp")
  cpp4r_hpp_path <- file.path(parent_dir, "cpp4r.hpp")

  if (file.exists(armadillo4r_hpp_path)) {
    unlink(armadillo4r_hpp_path)
  }

  if (file.exists(cpp4r_hpp_path)) {
    unlink(cpp4r_hpp_path)
  }

  if (is_interactive()) {
    message("Unvendored cpp4r and armadillo4r from '", parent_dir, "'")
    message("\nDESCRIPTION should link to cpp4r and armadillo4r (e.g., 'LinkingTo: cpp4r, armadillo4r')")
  }

  unlink(info_file)

  invisible(TRUE)
}
