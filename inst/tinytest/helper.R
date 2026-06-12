local_package <- function() {
  dir <- tempfile()
  dir.create(dir)
  do.call(
    "on.exit",
    list(bquote(unlink(.(dir), recursive = TRUE)), TRUE),
    envir = parent.frame()
  )
  writeLines("Package: testPkg", file.path(dir, "DESCRIPTION"))
  writeLines("useDynLib(testPkg, .registration = TRUE)", file.path(dir, "NAMESPACE"))
  desc::desc(dir)
}

pkg_path <- function(pkg) {
  dirname(pkg$.__enclos_env__$private$path)
}
