#!/bin/bash
echo "Starting plot.."
gnuplot <<__EOF
set datafile separator ","
set term png size 1500,800 crop
set title "REIS Solar Irradiance Sensor Test -- Voltages"
set xdata time
set timefmt "%Y-%m-%d %H:%M:%S."
set ylabel "Sensor Voltage (V * 100)"
set yrange [0:7000]
set xtics format "%d %H:%M"
set output "voltage.png"
plot 'outdoor_env_threeday.csv' using 2:9 pt 10 ps 0.25 lt rgb "red" title 'solar voltage samples' with lines, \
    'outdoor_env_threeday.csv' using 2:7 pt 10 ps 0.25 lt rgb "blue" title 'panel mv samples' with lines, \
    'outdoor_env_threeday.csv' using 2:6 pt 10 ps 0.25 lt rgb "green" title 'battery mv samples' with lines
pause -1
__EOF
rsync -az "voltage.png" webfaction:~/homepage/scel
#set format x "%m/%d/%Y %H:%M:%S"
#plot "log.csv" u 1:2 w l, f(x) line 5
