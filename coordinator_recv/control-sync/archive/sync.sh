#!/usr/bin/env bash


addresses=["151,156"]

for item in $addresses 
do
    echo $item
done


while true
do
    # Dump the postgres database to a csv file
    echo "Script is active: $(date)"
    echo
    psql -c '\copy (SELECT * FROM outdoor_env WHERE apogee_w_m2 IS NOT NULL) To outdoor_env.csv With CSV header'
    psql -c '\copy (SELECT * FROM outdoor_env WHERE (apogee_w_m2 IS NOT NULL AND address=156) ORDER BY db_time DESC) To outdoor_env_threeday.csv With CSV header'
    rsync -az --progress -h outdoor_env.csv webfaction:~/homepage/scel
    rsync -az --progress -h outdoor_env_threeday.csv webfaction:~/homepage/scel
    ./graph_threeday.sh
    echo "Script is done: $(date)"
    echo
    echo "Script is sleeping now."
    sleep 900
done
