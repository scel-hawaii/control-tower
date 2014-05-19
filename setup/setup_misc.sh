#!/bin/bash
# Some leftover misc setup scripts

# Add the REIS and current user to the dialout group
# We need this to have access to serial communication
sudo adduser reis dialout
sudo adduser $USER dialout
