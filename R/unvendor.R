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

  # The info file is in the armadillo4r directory, so dirname gives us the armadillo4r directory
  armadillo4r_dir <- dirname(info_file)
  # The parent of the armadillo4r directory is where armadillo4r.hpp should be
  parent_dir <- dirname(armadillo4r_dir)

  # Remove the armadillo4r directory
  unlink(armadillo4r_dir, recursive = TRUE)

  # Remove armadillo4r.hpp from the parent directory
  armadillo4r_hpp_path <- file.path(parent_dir, "armadillo4r.hpp")
  if (file.exists(armadillo4r_hpp_path)) {
    unlink(armadillo4r_hpp_path)
  }

  # Use the parent directory from the first info file for the message
  final_parent_dir <- dirname(dirname(info_file[1]))

  if (is_interactive()) {
    message("Unvendored armadillo4r from '", final_parent_dir, "'")
    message("DESCRIPTION should link to cpp4r and armadillo4r (e.g., 'LinkingTo: cpp4r, armadillo4r')")
  }

  invisible(final_parent_dir)
}
