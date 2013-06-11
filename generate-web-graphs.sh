#!/bin/bash

export PGHOST=localhost
export PGPORT=5432
export PGUSER=sensornet
export PGDATABASE=sensing_monitoring

psql -c "\copy (SELECT address, round_time_5min(db_time) AS db_time_5min, count(*) AS n, min(bmp085_temp_decic) AS min_bmp085_temp_decic, avg(bmp085_temp_decic)::integer AS avg_bmp085_temp_decic, max(bmp085_temp_decic) AS max_bmp085_temp_decic, min(bmp085_press_pa) AS min_bmp085_press_pa, avg(bmp085_press_pa)::integer AS avg_bmp085_press_pa, max(bmp085_press_pa) AS max_bmp085_press_pa, min(batt_mv) AS min_batt_mv, avg(batt_mv)::integer AS avg_batt_mv, max(batt_mv) AS max_batt_mv, min(panel_mv) AS min_panel_mv, avg(panel_mv)::integer AS avg_panel_mv, max(panel_mv) AS max_panel_mv, min(uptime_ms) AS min_uptime_ms, avg(uptime_ms)::integer AS avg_uptime_ms, max(uptime_ms) AS max_uptime_ms, min(apogee_w_m2) AS min_apogee_w_m2, avg(apogee_w_m2)::integer AS avg_apogee_w_m2, max(apogee_w_m2) AS max_apogee_w_m2 FROM outdoor_env WHERE db_time > now() - '24 hours'::interval GROUP BY address, round_time_5min(db_time) ORDER BY db_time_5min) to results_today.csv.new csv header" &

psql -c "\copy (select * from outdoor_env_5min) to results_all.csv.new csv header" &

psql -c "\copy (SELECT address, round_time_5min(db_time) AS db_time_5min, count(*) AS n, min(bmp085_temp_decic) AS min_bmp085_temp_decic, avg(bmp085_temp_decic)::integer AS avg_bmp085_temp_decic, max(bmp085_temp_decic) AS max_bmp085_temp_decic, min(bmp085_press_pa) AS min_bmp085_press_pa, avg(bmp085_press_pa)::integer AS avg_bmp085_press_pa, max(bmp085_press_pa) AS max_bmp085_press_pa, min(batt_mv) AS min_batt_mv, avg(batt_mv)::integer AS avg_batt_mv, max(batt_mv) AS max_batt_mv, min(panel_mv) AS min_panel_mv, avg(panel_mv)::integer AS avg_panel_mv, max(panel_mv) AS max_panel_mv, min(uptime_ms) AS min_uptime_ms, avg(uptime_ms)::integer AS avg_uptime_ms, max(uptime_ms) AS max_uptime_ms, min(apogee_w_m2) AS min_apogee_w_m2, avg(apogee_w_m2)::integer AS avg_apogee_w_m2, max(apogee_w_m2) AS max_apogee_w_m2 FROM outdoor_env WHERE db_time > now() - '7 days'::interval GROUP BY address, round_time_5min(db_time) ORDER BY db_time_5min) to results_week.csv.new csv header" &

psql --html -c "select address, date_trunc('hour', db_time) as db_hr, count(*) as n, round(max(uptime_ms)::numeric/1000/3600, 2) as max_uptime_hr, avg(bmp085_temp_decic)::integer as avg_temp, avg(bmp085_press_pa)::integer as avg_press, avg(batt_mv)::integer as avg_batt, avg(panel_mv)::integer as avg_panel, avg(apogee_w_m2)::integer as avg_apogee_w_m2 from outdoor_env where db_time > now() - '12 hours'::interval group by address, db_hr order by address, db_hr desc;" > summary_table.html &

psql -c '\copy outdoor_env to outdoor_env.csv.new csv header' &

uniq_addresses() { 
    # Pick out the unique device addresses in a CSV read on stdin.
    # (Keeps each first field seen starting at the second record [to
    # skip the header] in an associative array d, then prints out each
    # key k.) Likely will fail if the first field contains whitespace.
    awk -F, '{if (NR > 1) d[$1]++} END {for (k in d) printf "%s ", k}'
}

addresses_all=$(uniq_addresses < results_all.csv)
addresses_today=$(uniq_addresses < results_today.csv)
addresses_week=$(uniq_addresses < results_week.csv)

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
plot for [f in "${addresses_all}"] "< grep '^".f.",' results_all.csv" using 2:5 title "node ".f

set title "Sensor pressures, all time."
set ylabel "pressure (Pa)"
set output "all_press.png.new"
plot for [f in "${addresses_all}"] "< grep '^".f.",' results_all.csv" using 2:8 title "node ".f

set title "Sensor battery voltages, all time."
set ylabel "battery voltage (mV)"
set output "all_batt.png.new"
plot for [f in "${addresses_all}"] "< grep '^".f.",' results_all.csv" using 2:11 title "node ".f

set title "Sensor panel voltages, all time."
set ylabel "panel voltage (mV)"
set output "all_panels.png.new"
plot for [f in "${addresses_all}"] "< grep '^".f.",' results_all.csv" using 2:14 title "node ".f

set title "Solar irradiance, all time."
set ylabel "irradiance (w/m^2)"
set output "all_irrad.png.new"
plot for [f in "${addresses_all}"] "< grep '^".f.",' results_all.csv" using 2:20 title "node ".f
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
plot for [f in "${addresses_today}"] "< grep '^".f.",' results_today.csv" using 2:5 title "node ".f

set title "Sensor pressures, past 24 hours."
set ylabel "pressure (Pa)"
set output "today_press.png.new"
plot for [f in "${addresses_today}"] "< grep '^".f.",' results_today.csv" using 2:8 title "node ".f

set title "Sensor battery voltages, past 24 hours."
set ylabel "battery voltage (mV)"
set output "today_batt.png.new"
plot for [f in "${addresses_today}"] "< grep '^".f.",' results_today.csv" using 2:11 title "node ".f

set title "Sensor panel voltages, past 24 hours."
set ylabel "panel voltage (mV)"
set output "today_panels.png.new"
plot for [f in "${addresses_today}"] "< grep '^".f.",' results_today.csv" using 2:14 title "node ".f

set title "Solar irradiance, past 24 hours."
set ylabel "irradiance (w/m^2)"
set output "today_irrad.png.new"
plot for [f in "${addresses_today}"] "< grep '^".f.",' results_today.csv" using 2:20 title "node ".f
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
plot for [f in "${addresses_week}"] "< grep '^".f.",' results_week.csv" using 2:5 title "node ".f

set title "Sensor pressures, past week."
set ylabel "pressure (Pa)"
set output "week_press.png.new"
plot for [f in "${addresses_week}"] "< grep '^".f.",' results_week.csv" using 2:8 title "node ".f

set title "Sensor battery voltages, past week."
set ylabel "battery voltage (mV)"
set output "week_batt.png.new"
plot for [f in "${addresses_week}"] "< grep '^".f.",' results_week.csv" using 2:11 title "node ".f

set title "Sensor panel voltages, past week."
set ylabel "panel voltage (mV)"
set output "week_panels.png.new"
plot for [f in "${addresses_week}"] "< grep '^".f.",' results_week.csv" using 2:14 title "node ".f

set title "Solar irradiance, past week."
set ylabel "irradiance (w/m^2)"
set output "week_irrad.png.new"
plot for [f in "${addresses_week}"] "< grep '^".f.",' results_week.csv" using 2:20 title "node ".f
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

    cat summary_table.html

    echo "<a href=\"generate-web-graphs.sh\">code</a>"

    echo "</html>"
) > index.html.new

mv index.html.new index.html
