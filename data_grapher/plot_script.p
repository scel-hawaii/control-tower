set datafile separator ","
set term png size 1000,700 crop

set timefmt "%Y-%m-%d %H:%M:%S"
set xdata time

set output 'public_html/apple/solar_irr.png'
set xlabel "Date/Time"
set ylabel "Solar Irr Sensor mV"
plot 'apple_data.csv' using 9:1 title "solar irr" pt 7 ps 0.5

set output 'public_html/apple/batt_mv.png'
set xlabel "Date/Time"
set ylabel "Battery mV"
plot 'apple_data.csv' using 9:2 title "batt_mv" pt 7 ps 0.5

set output 'public_html/apple/humidity.png'
set xlabel "Date/Time"
set ylabel "Humidity pct"
plot 'apple_data.csv' using 9:3 title "humidity" pt 7 ps 0.5

set output 'public_html/apple/temperature.png'
set xlabel "Date/Time"
set ylabel "Temperature (centi-kelvin)"
plot 'apple_data.csv' using 9:8 title "temperature" pt 7 ps 0.5

set output 'public_html/apple/pressure.png'
set xlabel "Date/Time"
set ylabel "Pressure (pa)"
plot 'apple_data.csv' using 9:6 title "pressure" pt 7 ps 0.5

set output 'public_html/apple/uptime_ms.png'
set xlabel "Date/Time"
set ylabel "Uptime (ms)"
plot 'apple_data.csv' using 9:10 title "uptime_ms" pt 7 ps 0.5

set output 'public_html/apple/panel_mv.png'
set xlabel "Date/Time"
set ylabel "Panel (mV)"
plot 'apple_data.csv' using 9:5 title "panel_mv" pt 7 ps 0.5

set output 'public_html/cranberry/solar_irr.png'
set xlabel "Date/Time"
set ylabel "Solar Irr Sensor mV"
plot 'cranberry_data.csv' using 9:1 title "solar irr" with line

set output 'public_html/cranberry/batt_mv.png'
set ylabel "Battery mV"
plot 'cranberry_data.csv' using 9:2 title "batt_mv" with line

set output 'public_html/cranberry/humidity.png'
set ylabel "Humidity pct"
plot 'cranberry_data.csv' using 9:3 title "humidity" with line

set output 'public_html/cranberry/temperature.png'
set ylabel "Temperature (centi-kelvin)"
plot 'cranberry_data.csv' using 9:8 title "temperature" with line

set output 'public_html/cranberry/pressure.png'
set ylabel "Pressure (pa)"
plot 'cranberry_data.csv' using 9:6 title "pressure" with line

set output 'public_html/cranberry/uptime_ms.png'
set ylabel "Uptime (ms)"
plot 'cranberry_data.csv' using 9:10 title "uptime_ms" with line

set output 'public_html/cranberry/panel_mv.png'
set ylabel "Panel (mV)"
plot 'cranberry_data.csv' using 9:5 title "panel_mv" with line

