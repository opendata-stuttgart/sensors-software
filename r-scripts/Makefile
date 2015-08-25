R_OPTS=--no-save --no-restore --no-init-file --no-site-file # vanilla, but with --environ

# TODO: define all targets from source files, if possible

all: readdata.RData

%.pdf: %.Rmd 
	R ${R_OPTS} -e "library(knitr); knit2pdf('$<')"

%.pdf: %.rmd
	R ${R_OPTS} -e "library(knitr); knit2pdf('$<')"

%.html: %.rmd
	R ${R_OPTS} -e "rmarkdown::render('$<')"

%.html: %.Rmd
	R ${R_OPTS} -e "rmarkdown::render('$<')"

# Note that you could also use
#	R ${R_OPTS} -e "markdown::markdownToHTML('markdown_example.md', 'markdown_example.html')"

%.R: %.Rmd
	R ${R_OPTS} -e "library(knitr);knit('$<',tangle=TRUE)"

# run R script and save workspace, e.g. 
# make gendataexample.RData
%.RData: %.R
	# delete output (to be created by script)
	$(RM) $@
	R ${R_OPTS} -e 'source("$<"); save(list=ls(),file="$@")'

# TODO
# clean:
# 	rm

