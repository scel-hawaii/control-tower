#!/bin/bash
input_file=$1
output_file=$2
gnuplot <<__EOF
set datafile separator ","
set term png size 1500,800 crop
set title "REIS Solar Irradiance Sensor Test -- Voltages"
set xdata time
set timefmt "%Y-%m-%d %H:%M:%S."
set ylabel "Sensor Voltage (V * 100)"
set yrange [0:7000]
set xtics format "%d %H:%M"
set output "$output_file"
plot '$input_file' using 2:9 pt 10 ps 0.25 lt rgb "red" title 'solar voltage samples' with lines, \
    '$input_file' using 2:7 pt 10 ps 0.25 lt rgb "blue" title 'panel mv samples' with lines, \
    '$input_file' using 2:6 pt 10 ps 0.25 lt rgb "green" title 'battery mv samples' with lines
pause -1
__EOF
