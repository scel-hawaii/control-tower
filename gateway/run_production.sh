#!/bin/bash

# If the python virtualenv isn't setup, set it up:
#   http://docs.python-guide.org/en/latest/dev/virtualenvs/
if [ ! -d "env" ]; then
    echo "Setting up python virtual environment for the first time (this only needs to be done once)..."
    echo "This may take a couple of minutes..."
    ./setup_venv.sh
fi

source env/bin/activate
# production database uri
export GATEWAY_DB_URI="postgresql://gateway@localhost/weatherbox"

echo "Starting Server"
cd src && python gateway_server.py $@

