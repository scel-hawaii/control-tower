#!/bin/bash
#
# This script sets up the correct udev rules for the avrisp-mkii to
# work properly with the arduino ide.
#
# BE SURE TO RUN THIS AS ROOT, AND TO REPLACE THE 'REIS' USERNAME WITH 
# THE PROPER USERNAME

cp 99-avrisp.rules /etc/udev/rules.d/99-avrisp.rules
adduser reis uucp

