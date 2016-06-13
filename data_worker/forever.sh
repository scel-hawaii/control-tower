#!/bin/bash
# Simple script to keep restarting the python process just in case we have a crash.
while true
do
python worker.py
sleep 1
done
