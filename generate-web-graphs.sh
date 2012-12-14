#!/bin/bash

psql -h localhost -U reis reis -c "\copy (select * from min_max_avg_5min where db_time_5min > now() - '24 hours'::interval) to results_today.csv.new csv header" &

psql -h localhost -U reis reis -c "\copy (select * from min_max_avg_5min) to results_all.csv.new csv header" &

psql -h localhost -U reis reis -c "\copy (select * from min_max_avg_5min where db_time_5min > now() - '7 days'::interval) to results_week.csv.new csv header" &

wait

for f in *.csv.new; do mv "$f" "${f%.new}"; done

gnuplot << __EOF__ &
set datafile separator ","
set xdata time
set timefmt "%Y-%m-%d %H:%M:%S-10"
set format x "%Y-%m-%d\n%H:%M"
set style data lines
set key bottom right
set terminal png size 1400,800

set title "Sensor temperatures, all time."
set ylabel "temperature (dC)"
set output "all_temps.png.new"
plot "< grep '^544,' results_all.csv" using 2:5 title "node 544", "< grep '^545,' results_all.csv" using 2:5 title "node 545", "< grep '^546,' results_all.csv" using 2:5 title "node 546" # temps

set title "Sensor pressures, all time."
set ylabel "pressure (Pa)"
set output "all_press.png.new"
plot "< grep '^544,' results_all.csv" using 2:8 title "node 544", "< grep '^545,' results_all.csv" using 2:8 title "node 545", "< grep '^546,' results_all.csv" using 2:8 title "node 546" # press

set title "Sensor battery voltages, all time."
set ylabel "battery voltage (mV)"
set output "all_batt.png.new"
plot "< grep '^544,' results_all.csv" using 2:11 title "node 544", "< grep '^545,' results_all.csv" using 2:11 title "node 545", "< grep '^546,' results_all.csv" using 2:11 title "node 546" # batteries

set title "Sensor panel voltages, all time."
set ylabel "panel voltage (mV)"
set output "all_panels.png.new"
plot "< grep '^544,' results_all.csv" using 2:14 title "node 544", "< grep '^545,' results_all.csv" using 2:14 title "node 545", "< grep '^546,' results_all.csv" using 2:14 title "node 546" # panels

set title "Solar irradiance, all time."
set ylabel "irradiance (w/m^2)"
set output "all_irrad.png.new"
plot "< grep '^544,' results_all.csv" using 2:20 title "node 544", "< grep '^545,' results_all.csv" using 2:20 title "node 545", "< grep '^546,' results_all.csv" using 2:20 title "node 546" # irradiance
__EOF__

gnuplot << __EOF__ &
set datafile separator ","
set xdata time
set timefmt "%Y-%m-%d %H:%M:%S-10"
set format x "%Y-%m-%d\n%H:%M"
set style data lines
set key bottom right
set terminal png size 1400,800

set title "Sensor temperatures, past 24 hours."
set ylabel "temperature (dC)"
set output "today_temps.png.new"
plot "< grep '^544,' results_today.csv" using 2:5 title "node 544", "< grep '^545,' results_today.csv" using 2:5 title "node 545", "< grep '^546,' results_today.csv" using 2:5 title "node 546" # temps

set title "Sensor pressures, past 24 hours."
set ylabel "pressure (Pa)"
set output "today_press.png.new"
plot "< grep '^544,' results_today.csv" using 2:8 title "node 544", "< grep '^545,' results_today.csv" using 2:8 title "node 545", "< grep '^546,' results_today.csv" using 2:8 title "node 546" # press

set title "Sensor battery voltages, past 24 hours."
set ylabel "battery voltage (mV)"
set output "today_batt.png.new"
plot "< grep '^544,' results_today.csv" using 2:11 title "node 544", "< grep '^545,' results_today.csv" using 2:11 title "node 545", "< grep '^546,' results_today.csv" using 2:11 title "node 546" # batteries

set title "Sensor panel voltages, past 24 hours."
set ylabel "panel voltage (mV)"
set output "today_panels.png.new"
plot "< grep '^544,' results_today.csv" using 2:14 title "node 544", "< grep '^545,' results_today.csv" using 2:14 title "node 545", "< grep '^546,' results_today.csv" using 2:14 title "node 546" # panels

set title "Solar irradiance, past 24 hours."
set ylabel "irradiance (w/m^2)"
set output "today_irrad.png.new"
plot "< grep '^544,' results_today.csv" using 2:20 title "node 544", "< grep '^545,' results_today.csv" using 2:20 title "node 545", "< grep '^546,' results_today.csv" using 2:20 title "node 546" # irradiance
__EOF__

gnuplot << __EOF__ &
set datafile separator ","
set xdata time
set timefmt "%Y-%m-%d %H:%M:%S-10"
set format x "%Y-%m-%d\n%H:%M"
set style data lines
set key bottom right
set terminal png size 1400,800

set title "Sensor temperatures, past week."
set ylabel "temperature (dC)"
set output "week_temps.png.new"
plot "< grep '^544,' results_week.csv" using 2:5 title "node 544", "< grep '^545,' results_week.csv" using 2:5 title "node 545", "< grep '^546,' results_week.csv" using 2:5 title "node 546" # temps

set title "Sensor pressures, past week."
set ylabel "pressure (Pa)"
set output "week_press.png.new"
plot "< grep '^544,' results_week.csv" using 2:8 title "node 544", "< grep '^545,' results_week.csv" using 2:8 title "node 545", "< grep '^546,' results_week.csv" using 2:8 title "node 546" # press

set title "Sensor battery voltages, past week."
set ylabel "battery voltage (mV)"
set output "week_batt.png.new"
plot "< grep '^544,' results_week.csv" using 2:11 title "node 544", "< grep '^545,' results_week.csv" using 2:11 title "node 545", "< grep '^546,' results_week.csv" using 2:11 title "node 546" # batteries

set title "Sensor panel voltages, past week."
set ylabel "panel voltage (mV)"
set output "week_panels.png.new"
plot "< grep '^544,' results_week.csv" using 2:14 title "node 544", "< grep '^545,' results_week.csv" using 2:14 title "node 545", "< grep '^546,' results_week.csv" using 2:14 title "node 546" # panels

set title "Solar irradiance, past week."
set ylabel "irradiance (w/m^2)"
set output "week_irrad.png.new"
plot "< grep '^544,' results_week.csv" using 2:20 title "node 544", "< grep '^545,' results_week.csv" using 2:20 title "node 545", "< grep '^546,' results_week.csv" using 2:20 title "node 546" # irradiance
__EOF__

wait

for f in *.png.new; do mv "$f" "${f%.new}"; done

(
    echo "<html>"
    echo "<p>$(date). Each graph shows average readings over each 5-minute interval. Sample period about 15 seconds.<br>"

    echo "<ul>"
    for f in *.csv; do 
	echo "  <li><a href=\"${f}\">${f}</a> ($(stat -c %s "${f}") bytes)</li>"
    done
    echo "</ul>"

    for f in today_*.png week_*.png all_*.png; do 
	echo "  <a href=\"${f}\"><img src=\"${f}\"></a><br>"
    done

    echo "<a href=\"graphify.sh\">code</a>"

    echo "</html>"
) > index.html.new

mv index.html.new index.html
