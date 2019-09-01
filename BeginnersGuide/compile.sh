#!/bin/bash

for i in *.md
do
target="$i.pdf"
echo "$i -> $target" 
pandoc --toc -V classoption:DIV21 -V colorlinks:true -V documentclass:scrartcl --pdf-engine=xelatex -fmarkdown+autolink_bare_uris+lists_without_preceding_blankline -o "$target" "$i"
done
