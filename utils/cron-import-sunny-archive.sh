#!/bin/bash

# Import Sunny Webbox data from the Java polling program into the
# sensing_monitoring database. Requires a sunny_webbox_flat table and
# creates a sunny_webbox_flat_import table to hold intermediate
# results. Run this through cron under the sensornet user on the
# database box.

# Create the sunny_webbox_flat table like:
#   CREATE TABLE sunny_webbox_flat (LIKE sunny_webbox_flat_import);
# when the intermediate table is present.

# example crontab line:
# @hourly /wherever/cron-import-sunny-archive.sh

set -x
set -e

export PGUSER=sensornet
export PGDATABASE=sensing_monitoring

# Find read-sunny-archive.py next to this script
SQL_EXPORT_TOOL="$(dirname $(readlink -f $0))/read-sunny-archive.py"

cd /home/garmire/archives || exit 1

prefixes=$(ls | sed 's,^\([0-9]*\)\..*$,\1,g' | uniq | grep '^[0-9]*$')
# For each unique numeric prefix, in order...
for p in $prefixes; do
    python $SQL_EXPORT_TOOL "$p" | psql --single-transaction > /dev/null
    psql -c 'insert into sunny_webbox_flat (select * from sunny_webbox_flat_import where time > (select max(time) from sunny_webbox_flat));'
done
psql -c 'drop table sunny_webbox_flat_import;'
