#!/bin/bash

#
# seed.sh
#
# Author: Kenny Luong <luong97@hawaii.edu>
# Date: 09/24/2016
#
# This script will 'seed' the database with some real weatherbox data
# and allow anyone to get started using this platform.
#
# This script ASSUMES that the database schema has already been setup.
#
#

# Fetch seed data
echo 'Fetching dataset...'
wget http://static.scel-hawaii.org/data/outdoor_env.csv.zip
unzip outdoor_env.csv.zip
echo 'Done fetching dataset.'

# Import to machine db

echo 'Importing dataset into database...'
psql -c "\\copy outdoor_env FROM 'outdoor_env.csv' CSV HEADER"
echo 'Done importing dataset.'
