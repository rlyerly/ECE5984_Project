#!/usr/bin/gnuplot

filename="`echo $FILENAME`"
outfile="`echo $OUTPUT`"
thisTitle="`echo $TITLE`"

set title thisTitle
set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set xrange [-1:32]
set auto y

set term png
set output outfile
plot filename using 1 title 'zeroes', \
        '' using 2 title 'ones'
