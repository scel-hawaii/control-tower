#!/usr/bin/env python

from xbee import ZigBee
from serial import Serial
import sys
import time

time_fmt = '%FT%T %z'

try:
    ser = Serial(sys.argv[1], 9600)
except IndexError:
    ser = Serial('/dev/ttyUSB0', 9600)
xbee = ZigBee(ser, escaped=True)

print time.strftime(time_fmt),
print "starting..."

while True:
    try:
        values_str = xbee.wait_read_frame()['rf_data']
        print time.strftime(time_fmt),
        print values_str
        sys.stdout.flush()
    except:
        print time.strftime(time_fmt),
        print "ser.close()"
        ser.close()
        raise
