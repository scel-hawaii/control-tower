#!/bin/bash

#
# setup_sample_tables.sh
# Author: Kenny Luong <luong97@hawaii.edu>
# Modded: Tim Byers
#
# This sets up a database for the control_tower user.
#

function postgres_command(){
    sudo -u postgres psql -U postgres -d template1 -c "$1"
    exit_status=$?
    if [ $exit_status != 0 ]; then
        echo "ERROR PSQL FAILED WITH COMMAND: $1"
        # exit $exit_status
    fi
}

function import_db_dump(){
    sudo -u control_tower psql -U control_tower < "old_multi_table.sql"
}

function check_user(){
    if id -u 'control_tower' >/dev/null 2>&1; then
            echo "user exists"
    else
            echo "ERROR: user does not exist"
            sudo adduser control_tower --disabled-password --gecos ""
            # We don't want to exit after this
            # exit 1
    fi
}

tar -xvf old_data.tar
check_user
postgres_command "CREATE USER control_tower WITH PASSWORD 'password'"
postgres_command "CREATE DATABASE control_tower"
postgres_command "GRANT ALL PRIVILEGES ON DATABASE control_tower to control_tower"
import_db_dump
postgres_command "BULK INSERT heartbeat FROM 'heartbeat_.csv' WITH (FIELDTERMINATOR = ',',ROWTERMINATOR = '\n')"
postgres_command "BULK INSERT apple FROM 'apple_old.csv' WITH (FIELDTERMINATOR = ',',ROWTERMINATOR = '\n')"
postgres_command "BULK INSERT cranberry FROM 'cranberry_old.csv' WITH (FIELDTERMINATOR = ',',ROWTERMINATOR = '\n')"
postgres_command "BULK INSERT dragonfruit FROM 'dragonfruit_old.csv' WITH (FIELDTERMINATOR = ',',ROWTERMINATOR = '\n')"

echo "Script Success. Finished setting up database."

