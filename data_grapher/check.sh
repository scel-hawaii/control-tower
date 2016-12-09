#!/bin/bash
# A simple script that checks the last date written in a CSV file
# written by the gateway script.
#
# This script isn't needed for anything but may be useful in the future,
# or if you want an easy way to check.
#

tail -n 1 /home/control_tower/data-gateway/Gateway_v2/cranberry_data.csv | tr ',' "\n" | sed -n 9p
tail -n 1 /home/control_tower/data-gateway/Gateway_v2/dragonfruit_data.csv | tr ',' "\n" | sed -n 9p
