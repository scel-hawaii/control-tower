#!/bin/sh

# Install sensor network coordinator component system-wide. Assumes
# `sensornet' user exists. Logs everything to /var/log/messages by
# default.

cp coordinator-recv-db ../coordinator-recv-db.py /usr/local/libexec/
cp coordinator-recv-db.conf /etc/init/

# Run, e.g., initctl start/stop/restart coordinator-recv-db to control
# the service.
