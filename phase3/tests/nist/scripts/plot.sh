#!/bin/bash

TESTS=('Frequency' 'BlockFrequency' 'CumulativeSums' 'Runs' 'LongestRun' 'Rank' 'FFT' 'NonOverlappingTemplate' 'OverlappingTemplate' 'Universal' 'ApproximateEntropy' 'RandomExcursions' 'RandomExcursionsVariant' 'Serial' 'LinearComplexity')

rm converted_results/*
cp ../results/* converted_results/

for file in converted_results/*
do
    #delete arbitrary lines
    #sed '1,7d' ${file} > ${file}.tmp
    #sed '196,207d' ${file}.tmp > ${file}.shrunk # might want to pull out the threshold before deleting this

    #averaging here
    for temp in ${TESTS[*]}
    do
        echo ${temp} ${file}
        egrep -w "${temp}" ${file} | awk '{sum+=$12} END {print "",sum/NR "\t" $13}' >> ${file}.short
    done
        
    #cleanup
    #rm ${file} ${file}.tmp ${file}.shrunk
done

paste converted_results/*.short > converted_results/results_final.dat
