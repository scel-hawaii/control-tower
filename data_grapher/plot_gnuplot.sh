#!/bin/bash
# graph.

rsync -aHAX /home/control_tower/data-gateway/Gateway_v2/apple_data.csv public_html/
rsync -aHAX /home/control_tower/data-gateway/Gateway_v2/cranberry_data.csv public_html/
rsync -aHAX /home/control_tower/data-gateway/Gateway_v2/dragonfruit_data.csv public_html/
rsync -aHAX /home/control_tower/data-gateway/Gateway_v2/reset_log.txt public_html/

gnuplot plot_script.p
date > public_html/last_run.txt
