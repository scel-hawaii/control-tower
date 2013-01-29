#!/usr/bin/env python

from xbee import ZigBee
from serial import Serial
import psycopg2
import json

ser = Serial('/dev/ttyUSB0', 9600)
xbee = ZigBee(ser, escaped=True)

conn = psycopg2.connect(host="localhost", port="5432", user="reis", database="reis")
cur = conn.cursor()

insert_query = """begin; insert into raaargh (address, db_time, uptime_ms, bmp085_temp_decic, bmp085_press_pa, batt_mv, panel_mv, apogee_mv, apogee_w_m2) values (%(address)s, now(), %(uptime_ms)s, %(bmp085_temp_decic)s, %(bmp085_press_pa)s, %(batt_mv)s, %(panel_mv)s, %(apogee_mv)s, %(apogee_w_m2)s); commit;"""

print "starting..."

while True:
    try:
        values_str = xbee.wait_read_frame()['rf_data']
        print values_str
        values = json.loads(values_str)
        for field in ['apogee_mv', 'apogee_w_m2', 'address', 
                      'uptime_ms', 'bmp085_temp_decic', 
                      'bmp085_press_pa', 'batt_mv', 'panel_mv']:
            values.setdefault(field, None)
        cur.execute(insert_query, values)
    except:
        print "ser.close()"
        ser.close()
        cur.close()
        conn.close()
        raise
