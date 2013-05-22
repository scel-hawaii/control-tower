#!/usr/bin/env python

from xbee import ZigBee
from serial import Serial
import sys
import time

time_fmt = '%FT%T %z'

ser = Serial('/dev/ttyUSB1', 9600)
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
