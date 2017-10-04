#!/bin/bash

PS_OUTPUT=$(pgrep gateway_server.py)

if ! [ -z "$PS_OUTPUT" ]; then
    echo "Failure - the server is already running"
    exit
fi

echo "Starting Server"
cd src && python gateway_server.py auto

