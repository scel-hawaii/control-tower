#!/bin/bash

# If the python virtualenv isn't setup, set it up:
#   http://docs.python-guide.org/en/latest/dev/virtualenvs/
./setup_venv.sh

# production database uri
export GATEWAY_DB_URI="postgresql://gateway@localhost/weatherbox"

echo "Starting Server"
env/bin/python server.py --port $1

