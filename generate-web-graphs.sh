#!/bin/bash

psql -h localhost -U reis reis -c "\copy (select * from min_max_avg_5min where db_time_5min > now() - '24 hours'::interval) to results_today.csv.new csv header" &

psql -h localhost -U reis reis -c "\copy (select * from min_max_avg_5min) to results_all.csv.new csv header" &

psql -h localhost -U reis reis -c "\copy (select * from min_max_avg_5min where db_time_5min > now() - '3 hours'::interval) to results_hour.csv.new csv header" &

wait

for f in *.csv.new; do mv "$f" "${f%.new}"; done

gnuplot << __EOF__ &
set datafile separator ","
set xdata time
set timefmt "%Y-%m-%d %H:%M:%S-10"
set format x "%Y-%m-%d\n%H:%M"
set style data lines
set key off
set terminal png size 1400,800

set title "Sensor temperatures, all time."
set ylabel "temperature (dC)"
set output "all_temps.png.new"
plot "< grep '^544,' results_all.csv" using 2:4, "< grep '^544,' results_all.csv" using 2:5, "< grep '^544,' results_all.csv" using 2:6, "< grep '^545,' results_all.csv" using 2:4, "< grep '^545,' results_all.csv" using 2:5, "< grep '^545,' results_all.csv" using 2:6 # temps

set title "Sensor pressures, all time."
set ylabel "pressure (Pa)"
set output "all_press.png.new"
plot "< grep '^544,' results_all.csv" using 2:7, "< grep '^544,' results_all.csv" using 2:8, "< grep '^544,' results_all.csv" using 2:9, "< grep '^545,' results_all.csv" using 2:7, "< grep '^545,' results_all.csv" using 2:8, "< grep '^545,' results_all.csv" using 2:9 # press

set title "Sensor battery voltages, all time."
set ylabel "battery voltage (mV)"
set output "all_batt.png.new"
plot "< grep '^544,' results_all.csv" using 2:10, "< grep '^544,' results_all.csv" using 2:11, "< grep '^544,' results_all.csv" using 2:12, "< grep '^545,' results_all.csv" using 2:10, "< grep '^545,' results_all.csv" using 2:11, "< grep '^545,' results_all.csv" using 2:12 # batteries

set title "Sensor panel voltages, all time."
set ylabel "panel voltage (mV)"
set output "all_panels.png.new"
plot "< grep '^544,' results_all.csv" using 2:13, "< grep '^544,' results_all.csv" using 2:14, "< grep '^544,' results_all.csv" using 2:15, "< grep '^545,' results_all.csv" using 2:13, "< grep '^545,' results_all.csv" using 2:14, "< grep '^545,' results_all.csv" using 2:15 # panels

set title "Solar irradiance, all time."
set ylabel "irradiance (w/m^2)"
set output "all_irrad.png.new"
plot "< grep '^544,' results_all.csv" using 2:19, "< grep '^544,' results_all.csv" using 2:20, "< grep '^544,' results_all.csv" using 2:21, "< grep '^545,' results_all.csv" using 2:19, "< grep '^545,' results_all.csv" using 2:20, "< grep '^545,' results_all.csv" using 2:21 # irradiance
__EOF__

gnuplot << __EOF__ &
set datafile separator ","
set xdata time
set timefmt "%Y-%m-%d %H:%M:%S-10"
set format x "%Y-%m-%d\n%H:%M"
set style data lines
set key off
set terminal png size 1400,800

set title "Sensor temperatures, past 24 hours."
set ylabel "temperature (dC)"
set output "today_temps.png.new"
plot "< grep '^544,' results_today.csv" using 2:4, "< grep '^544,' results_today.csv" using 2:5, "< grep '^544,' results_today.csv" using 2:6, "< grep '^545,' results_today.csv" using 2:4, "< grep '^545,' results_today.csv" using 2:5, "< grep '^545,' results_today.csv" using 2:6 # temps

set title "Sensor pressures, past 24 hours."
set ylabel "pressure (Pa)"
set output "today_press.png.new"
plot "< grep '^544,' results_today.csv" using 2:7, "< grep '^544,' results_today.csv" using 2:8, "< grep '^544,' results_today.csv" using 2:9, "< grep '^545,' results_today.csv" using 2:7, "< grep '^545,' results_today.csv" using 2:8, "< grep '^545,' results_today.csv" using 2:9 # press

set title "Sensor battery voltages, past 24 hours."
set ylabel "battery voltage (mV)"
set output "today_batt.png.new"
plot "< grep '^544,' results_today.csv" using 2:10, "< grep '^544,' results_today.csv" using 2:11, "< grep '^544,' results_today.csv" using 2:12, "< grep '^545,' results_today.csv" using 2:10, "< grep '^545,' results_today.csv" using 2:11, "< grep '^545,' results_today.csv" using 2:12 # batteries

set title "Sensor panel voltages, past 24 hours."
set ylabel "panel voltage (mV)"
set output "today_panels.png.new"
plot "< grep '^544,' results_today.csv" using 2:13, "< grep '^544,' results_today.csv" using 2:14, "< grep '^544,' results_today.csv" using 2:15, "< grep '^545,' results_today.csv" using 2:13, "< grep '^545,' results_today.csv" using 2:14, "< grep '^545,' results_today.csv" using 2:15 # panels

set title "Solar irradiance, past 24 hours."
set ylabel "irradiance (w/m^2)"
set output "today_irrad.png.new"
plot "< grep '^544,' results_today.csv" using 2:19, "< grep '^544,' results_today.csv" using 2:20, "< grep '^544,' results_today.csv" using 2:21, "< grep '^545,' results_today.csv" using 2:19, "< grep '^545,' results_today.csv" using 2:20, "< grep '^545,' results_today.csv" using 2:21 # irradiance
__EOF__

gnuplot << __EOF__ &
set datafile separator ","
set xdata time
set timefmt "%Y-%m-%d %H:%M:%S-10"
set format x "%Y-%m-%d\n%H:%M"
set style data lines
set key off
set terminal png size 1400,800

set title "Sensor temperatures, past 3 hours."
set ylabel "temperature (dC)"
set output "hour_temps.png.new"
plot "< grep '^544,' results_hour.csv" using 2:4, "< grep '^544,' results_hour.csv" using 2:5, "< grep '^544,' results_hour.csv" using 2:6, "< grep '^545,' results_hour.csv" using 2:4, "< grep '^545,' results_hour.csv" using 2:5, "< grep '^545,' results_hour.csv" using 2:6 # temps

set title "Sensor pressures, past 3 hours."
set ylabel "pressure (Pa)"
set output "hour_press.png.new"
plot "< grep '^544,' results_hour.csv" using 2:7, "< grep '^544,' results_hour.csv" using 2:8, "< grep '^544,' results_hour.csv" using 2:9, "< grep '^545,' results_hour.csv" using 2:7, "< grep '^545,' results_hour.csv" using 2:8, "< grep '^545,' results_hour.csv" using 2:9 # press

set title "Sensor battery voltages, past 3 hours."
set ylabel "battery voltage (mV)"
set output "hour_batt.png.new"
plot "< grep '^544,' results_hour.csv" using 2:10, "< grep '^544,' results_hour.csv" using 2:11, "< grep '^544,' results_hour.csv" using 2:12, "< grep '^545,' results_hour.csv" using 2:10, "< grep '^545,' results_hour.csv" using 2:11, "< grep '^545,' results_hour.csv" using 2:12 # batteries

set title "Sensor panel voltages, past 3 hours."
set ylabel "panel voltage (mV)"
set output "hour_panels.png.new"
plot "< grep '^544,' results_hour.csv" using 2:13, "< grep '^544,' results_hour.csv" using 2:14, "< grep '^544,' results_hour.csv" using 2:15, "< grep '^545,' results_hour.csv" using 2:13, "< grep '^545,' results_hour.csv" using 2:14, "< grep '^545,' results_hour.csv" using 2:15 # panels

set title "Solar irradiance, past 3 hours."
set ylabel "irradiance (w/m^2)"
set output "hour_irrad.png.new"
plot "< grep '^544,' results_hour.csv" using 2:19, "< grep '^544,' results_hour.csv" using 2:20, "< grep '^544,' results_hour.csv" using 2:21, "< grep '^545,' results_hour.csv" using 2:19, "< grep '^545,' results_hour.csv" using 2:20, "< grep '^545,' results_hour.csv" using 2:21 # irradiance
__EOF__

wait

for f in *.png.new; do mv "$f" "${f%.new}"; done

(
    echo "<html>"
    echo "<p>$(date). Each graph includes min/avg/max per 5-minute interval. Sample period about 15 seconds.<br>"

    echo "<ul>"
    for f in *.csv; do 
	echo "  <li><a href=\"${f}\">${f}</a> ($(stat -c %s "${f}") bytes)</li>"
    done
    echo "</ul>"

    for f in today_*.png hour_*.png all_*.png; do 
	echo "  <a href=\"${f}\"><img src=\"${f}\"></a><br>"
    done

    echo "<a href=\"graphify.sh\">code</a>"

    echo "</html>"
) > index.html.new

mv index.html.new index.html
