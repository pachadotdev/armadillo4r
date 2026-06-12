local({
  dir <- tempdir()
  if (!dir.exists(dir)) {
    dir.create(dir)
  }
  expect_silent(pkg_template(dir, "testname"))
})
