#!/usr/bin/env python

from xbee import ZigBee
from serial import Serial
import psycopg2
import json
import sys
import time

import decode

time_fmt = '%FT%T %z'

try:
    ser = Serial(sys.argv[1], 9600)
except IndexError:
    ser = Serial('/dev/ttyUSB0', 9600)
xbee = ZigBee(ser, escaped=True)

conn = psycopg2.connect(host="localhost", port="5432", user="sensornet", password="easyp4ss!", database="sensing_monitoring")
cur = conn.cursor()

print time.strftime(time_fmt),
print "starting..."

while True:
    try:
        rf_data = xbee.wait_read_frame()['rf_data']

        try:
            cur.execute('BEGIN;')
            for t in decode.decode(rf_data):
                cur.execute(decode.create_query(t), t['values'])
            cur.execute('COMMIT;')
        except Exception, e:
            cur.execute('ROLLBACK;')
            cur.execute('BEGIN;')
            cur.execute(
                '''INSERT INTO outdoor_env_unrecognized (db_time, rf_data, exception) VALUES (now(), %s, %s);''',
                [buffer(rf_data), str(sys.exc_info()[0]) + ': ' + str(e)])
            cur.execute('COMMIT;')
            continue

    except:
        print time.strftime(time_fmt),
        print "stopping!"
        ser.close()
        cur.close()
        conn.close()
        raise
