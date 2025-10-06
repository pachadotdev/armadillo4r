#' Unvendor the armadillo4r headers
#'
#' This function removes the vendored armadillo4r headers from your package by
#' automatically finding the vendored headers.
#'
#' @param path The directory with the vendored headers
#' @return The path to the unvendored code (invisibly).
#' @export
#' @examples
#' # create a new directory
#' dir <- tempfile()
#' dir.create(dir)
#'
#' # vendor the armadillo4r headers into the directory
#' vendor(dir)
#'
#' # unvendor the armadillo4r headers from the directory
#' unvendor()
#'
#' # cleanup
#' unlink(dir, recursive = TRUE)
unvendor <- function(path = "./src/vendor") {
  suppressMessages(cpp4r::unvendor(path))

  # Find the vendoring info file
  info_files <- list.files(path, pattern = "00-armadillo4r-vendoring-info.txt", recursive = TRUE, full.names = TRUE)

  if (length(info_files) != 1L) {
    if (is_interactive()) { message("Could not find vendored headers") }
    return(invisible(NULL))
  }

  # The info file is in the armadillo4r directory, so dirname(info_files) gives us the armadillo4r directory
  armadillo4r_dir <- dirname(info_files)
  # The parent of the armadillo4r directory is where armadillo4r.hpp should be
  parent_dir <- dirname(armadillo4r_dir)
  
  # Remove the armadillo4r directory
  unlink(armadillo4r_dir, recursive = TRUE)

  # Remove armadillo4r.hpp from the parent directory
  armadillo4r_hpp_path <- file.path(parent_dir, "armadillo4r.hpp")
  if (file.exists(armadillo4r_hpp_path)) {
    unlink(armadillo4r_hpp_path)
  }

  if (is_interactive()) {
    message("Unvendored armadillo4r from '", parent_dir, "'")
    message("DESCRIPTION should link to cpp4r and armadillo4r (e.g., 'LinkingTo: cpp4r, armadillo4r')")
  }

  invisible(parent_dir)
}
