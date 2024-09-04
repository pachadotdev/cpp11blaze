clean:
	@Rscript -e 'devtools::clean_dll()'
	@Rscript -e 'devtools::clean_dll("cpp11blazetest")'

test:
	@echo "Testing R code"
	@Rscript -e 'devtools::document()'
	@Rscript -e 'devtools::load_all(); devtools::test()'
	@echo "Testing C++ code"
	@Rscript -e 'devtools::load_all("cpp11blazetest"); devtools::test("cpp11blazetest")'

check:
	@echo "Local"
	@Rscript -e 'devtools::document()'
	@Rscript -e 'devtools::check(); devtools::check("cpp11blazetest")'
	# this says "SSL certificate problem: self-signed certificate"
	# @echo "RHub"
	# @Rscript -e 'devtools::check_rhub()'
	# @echo "Win Builder"
	# @Rscript -e 'devtools::check_win_release()'
	# @Rscript -e 'devtools::check_win_devel()'

site:
	@Rscript -e 'devtools::document()'
	@Rscript -e 'pkgdown::build_site()'

install:
	@Rscript -e 'devtools::install()'

clang_format=`which clang-format-14`

format: $(shell find . -name '*.hpp') $(shell find . -name '*.cpp')
	@${clang_format} -i $?
