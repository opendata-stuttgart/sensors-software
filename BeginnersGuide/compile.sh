#!/bin/bash

targetdpi=150

for i in airrohr_set_howto_short.*.md
do

    target="$i.pdf"
    dpitarget="$i.${targetdpi}dpi.pdf"

    echo "$i -> $target"
    pandoc --toc -V classoption:DIV21 -V colorlinks:true -V documentclass:scrartcl --pdf-engine=xelatex -fmarkdown+autolink_bare_uris+lists_without_preceding_blankline -o "$target" "$i"
    
    echo "$target -> $dpitarget"
    gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dColorImageResolution="$targetdpi" -dColorImageDownsampleType=/Average -dGrayImageDownsampleType=/Average -dGrayImageResolution="$targetdpi" -dMonoImageResolution="$targetdpi" -dMonoImageDownsampleType=/Average -dOiptimize=true -dDownsampleColorImages=true -dDownsampleGrayImages=true -dDownsampleMonoImages=true -dColorConversionStrategy=/sRGB -dNOPAUSE -dQUIET -dBATCH -sOutputFile="${dpitarget}" "${target}"

done


