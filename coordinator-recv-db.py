#!/usr/bin/env python

from xbee import ZigBee
from serial import Serial
import psycopg2
import ast

ser = Serial('/dev/ttyUSB0', 9600)
xbee = ZigBee(ser, escaped=True)

conn = psycopg2.connect(host="localhost", port="5432", user="reis", database="reis")
cur = conn.cursor()

insert_query = """begin; insert into raaargh (address, db_time, uptime_ms, bmp085_temp_decic, bmp085_press_pa, batt_mv, panel_mv) values (%(address)s, now(), %(uptime_ms)s, %(bmp085_temp_decic)s, %(bmp085_press_pa)s, %(batt_mv)s, %(panel_mv)s); commit;"""

print "starting..."

while True:
    try:
        values = xbee.wait_read_frame()['rf_data']
        print values
        cur.execute(insert_query, ast.literal_eval(values))
    except:
        print "ser.close()"
        ser.close()
        cur.close()
        conn.close()
        raise
