#!/bin/bash
while [ 1 ];
number=$(cat log.csv | wc -l)
do
echo "Starting plot.."
gnuplot <<__EOF
set datafile separator ","
set term png size 1500,800 crop
set timefmt "%s"
set format x "%a %H:%M:%S%p"
set xdata time
set title "REIS Solar Irradiance Sensor Test -- Voltages"
set xlabel "Date and Time"
set ylabel "Sensor Voltage (V * 100)"
set yrange [0:500]
set xtics $number
set xtics format "%a %H:%M%p"
set output "voltage.png"
f(x) = a*x + b
fit f(x) 'log.csv' u 1:3 via a, b
plot 'log.csv' using 1:3 pt 7 ps 0.25 lt rgb "red" title 'battery voltage samples', f(x) lw 3 lt rgb "black" title 'battery voltage regression', 'log.csv' using 1:4 pt 7 ps 0.25 lt rgb "red" title 'calibrated sensor readings', 'log.csv' using 1:5 pt 7 ps 0.25 lt rgb "blue" title 'non-calibrated sensor readings', 'log.csv' using 1:6 pt 7 ps 0.25 lt rgb "green" title 'apogee sensor readings'
pause -1
__EOF
echo "Finished with plot..sleeping.."
sleep 300;
done
#set format x "%m/%d/%Y %H:%M:%S"
#plot "log.csv" u 1:2 w l, f(x) line 5
