# run this line if you want to replace all the files provided by the template
# cpp11blaze::pkg_template()

development <- TRUE

devtools::clean_dll()
cpp11::cpp_register()
devtools::document()

if (isTRUE(development)) {
  devtools::load_all()
} else {
  devtools::install()
}
