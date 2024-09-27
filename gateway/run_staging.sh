#!/bin/bash

./setup_venv.sh

# staging database uri
export GATEWAY_DB_URI="postgresql://control_tower_staging@localhost/control_tower_staging"

echo "Starting Server"
env/bin/python server.py $1

