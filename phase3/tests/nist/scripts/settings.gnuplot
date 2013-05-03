clear
reset
set title "NIST Pass Rates"
set ylabel "Avg. Passed Tests"
set key invert under nobox
#set key at graph .05,-.25 horizontal samplen 0.1
set auto x
set yrange [0:1]
#set ytics rotate out font "helvetica{,9}"
set xtics rotate out font "helvetica{,9}"
set style data histogram
set style histogram clustered gap 5
set style fill solid border -1
#set style fill solid 1.00 border lt -1
set boxwidth 0.95 
#set label 8 '/dev/urandom' at graph .05,-.35 left rotate by 90
#set label 7 '/dev/random' at graph .15,-.35 left rotate by 90
#set label 6 'gryo_raw' at graph .25,-.35 left rotate by 90
#set label 5 'gryo_filtered' at graph .35,-.35 left rotate by 90
#set label 4 '/dev/random + sensor data' at graph .45,-.35 left rotate by 90
#set label 3 'von neumann whitened' at graph .55,-.35 left rotate by 90
#set label 2 'accel_raw' at graph .65,-.35 left rotate by 90
#set label 1 'accel_filtered' at graph .75,-.35 left rotate by 90

set term png size 1280,800
set output "nist_results.png"
