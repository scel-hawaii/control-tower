#!/bin/sh

# Install sensor network coordinator component system-wide. Assumes
# `sensornet' user exists. Logs everything to /var/log/messages by
# default.

install -m 0755 coordinator-recv-db /usr/local/libexec/
install -m 0644 ../coordinator-recv-db.py ../decode.py /usr/local/libexec/
install -m 0644 coordinator-recv-db.conf /etc/init

# Run, e.g., initctl start/stop/restart coordinator-recv-db to control
# the service.
