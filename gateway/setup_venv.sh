#!/bin/bash
#
# If the python virtualenv isn't setup, set it up:
#   http://docs.python-guide.org/en/latest/dev/virtualenvs/
#
#

if [ -d "env" ]; then
    echo "Python virtual environment found, no need to setup again."
    exit 0
fi

echo "Setting up python virtual environment for the first time (this only needs to be done once)..."
echo "This may take a couple of minutes..."

python3 -m venv env
env/bin/pip3 install -r requirements.txt
