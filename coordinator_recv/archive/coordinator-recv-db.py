#!/usr/bin/env python

from xbee import ZigBee # Python Xbee library
from serial import Serial
import psycopg2 # Python PostgreSQL lib
import json # JSON handler (appears actually to be unused)
# Various low-level libs
import sys 
import time

import decode # where the hell is this being imported from

time_fmt = '%FT%T %z'

# Open serial port (Here the serial port is referenced by device name 
# according to current Linux spec. Depending on what port it was attached to,
# it may be ttyUSB1 or higher. The try: command first attempts to use the
# first USB port in the list.
try:
    ser = Serial(sys.argv[1], 9600)
except IndexError:
    ser = Serial('/dev/ttyUSB0', 9600)
xbee = ZigBee(ser, escaped=True) # Create ZigBee object on that serial port

# Create a DB connection object. This user must exist and have permission on
# the local DB.
# The password must also be valid.
conn = psycopg2.connect(host="localhost", port="5432", user="sensornet", password="easyp4ss!", database="sensing_monitoring")
# Do the actual connection based on the above
cur = conn.cursor()

print time.strftime(time_fmt),
print "starting..."

# Loop until killed
while True:
    try: # Try to get an xbee packet
        rf_data = xbee.wait_read_frame()['rf_data']

        try: # If we got a packet, try inserting it into the data
            cur.execute('BEGIN;') # Start a multiline command (possibly optional)
            # Splits packet by delimiters (list comprehension), enters
            for t in decode.decode(rf_data):
                cur.execute(decode.create_query(t), t['values'])
            cur.execute('COMMIT;') # Commits changes on the database
        except Exception, e:
            # If there is a database problem, undo the changes
            cur.execute('ROLLBACK;') 
            cur.execute('BEGIN;') # Put the bad data into a raw dump table
            cur.execute(
                '''INSERT INTO outdoor_env_unrecognized (db_time, rf_data, exception) VALUES (now(), %s, %s);''',
                [buffer(rf_data), str(sys.exc_info()[0]) + ': ' + str(e)])
            cur.execute('COMMIT;') # Commit changes
            continue

    except:
        # If we get a bad packet, print the time received, close all ports,
        # and die with error
        print time.strftime(time_fmt),
        print "stopping!"
        ser.close()
        cur.close()
        conn.close()
        raise
