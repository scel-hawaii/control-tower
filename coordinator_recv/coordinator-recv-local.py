#!/usr/bin/env python

from xbee import ZigBee
from serial import Serial
import sys
import time

import decode

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
        rf_data = xbee.wait_read_frame()['rf_data']
        print
        print
        print time.strftime(time_fmt)
        print rf_data
        try:
            time_points = decode.decode(rf_data)
            for t in time_points:
                print
                print 'time offset:', t['time_offset_s']
                print 'values:', t['values']
        except Exception as e:
            print 'exception:', str(e)
        sys.stdout.flush()
    except:
        print time.strftime(time_fmt),
        print "ser.close()"
        ser.close()
        raise
