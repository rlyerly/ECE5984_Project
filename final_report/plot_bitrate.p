#!/usr/bin/gnuplot
set title "Bitrate for different sources of data (bits/second)"
unset xtics
set logscale y
set yrange [1:100000000]
set key outside
set style fill solid border -1
set style data histogram

set term png
set output "bitrate.png"
plot "bitrate.txt" using 1 ti col, '' u 2 ti col, '' u 3 ti col, \
        '' u 4 ti col, '' u 5 ti col, '' u 6 ti col, '' u 7 ti col
