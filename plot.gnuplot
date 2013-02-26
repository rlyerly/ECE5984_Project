set terminal png 
set output "output.png"
set xrange [0:1024]
plot "<sed '1,2d' raw_data/blake256.raw.cycles | awk -f script.awk" u 1 w l t "blake256";
