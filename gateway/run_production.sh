#!/bin/bash

if [ ! -d "env" ]; then
    echo "Setting up python virtual environment for the first time (this only needs to be done once)..."
    echo "This may take a couple of minutes..."
    ./setup_venv.sh
fi

source env/bin/activate

PS_OUTPUT=$(pgrep gateway_server.py)

if ! [ -z "$PS_OUTPUT" ]; then
    echo "Failure - the server is already running"
    exit
fi

echo "Starting Server"
cd src && python gateway_server.py $@

