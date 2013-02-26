#!/bin/bash

#add them as they finish
for alg in blake256 blake32 blake512 blake64 cubehash816 groestl256 groestl512 jh224 jh256 jh384 jh512 keccak keccakc1024 keccakc256 keccakc418 keccakc512 keccakc768
do
    gnuplot -e "set xlabel \"Length of Hash\" ; set ylabel \"Number of Cycles\" ; set terminal png; set output \"${alg}.png\" ; set xrange [0:1024]; plot \"<sed '1,2d' raw_data/${alg}.raw.cycles | awk -f script.awk\" u 1 w l t \"${alg}\"; "
done
