#!/bin/bash

ALGOs=('blake256' 'blake32' 'blake512' 'blake64' 'cubehash816' 'groestl256'
       'groestl512' 'jh224' 'jh256' 'jh384' 'jh512' 'keccak' 'keccakc1024'
       'keccakc256' 'keccakc448' 'keccakc512' 'keccakc768' 'md5' 'mgrostl256'
       'sha256' 'sha512' 'skein10241024' 'skein256256' 'skein512256'
       'skein512512')

for alg in ${ALGOs[@]}
do
    gnuplot -e "set xlabel \"Length of Hash\" ; set ylabel \"Number of Cycles\" ; set terminal png; set output \"images_fast_run/${alg}.png\" ; set xrange [0:1024]; plot \"<sed '1,2d' fast_run_data/${alg}.raw.cycles | awk -f trimmed_mean.awk\" u 1 w l t \"${alg}\";"
done
