#!/bin/bash

TESTS=('Frequency' 'BlockFrequency' 'CumulativeSums' 'Runs' 'LongestRun' 'Rank' 'FFT' 'NonOverlappingTemplate' 'OverlappingTemplate' 'Universal' 'ApproximateEntropy' 'RandomExcursions' 'RandomExcursionsVariant' 'Serial' 'LinearComplexity')

rm converted_results/*
rm test_names.dat
cp ../results/* converted_results/

for temp in ${TESTS[*]}
do
    echo ${temp} >> test_names.dat
done


for file in converted_results/*
do
    #delete arbitrary lines
    #sed '1,7d' ${file} > ${file}.tmp
    #sed '196,207d' ${file}.tmp > ${file}.shrunk # might want to pull out the threshold before deleting this

    #averaging here
    for temp in ${TESTS[*]}
    do
        egrep -w "${temp}" ${file} | sed 's/\*//g' | awk '{sum+=$12} END {print "",sum/NR "\t"}' >> ${file}.short
    done
        
    #cleanup
    #rm ${file} ${file}.tmp ${file}.shrunk
done

paste converted_results/*.short test_names.dat > converted_results/results_final.dat

