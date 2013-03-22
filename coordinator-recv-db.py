#!/usr/bin/env python

from xbee import ZigBee
from serial import Serial
import psycopg2
import json
import sys
import time

time_fmt = '%FT%T %z'

ser = Serial('/dev/ttyUSB1', 9600)
xbee = ZigBee(ser, escaped=True)

conn = psycopg2.connect(host="localhost", port="5432", user="sensornet", password="easyp4ss!", database="sensing-monitoring")
cur = conn.cursor()

insert_query = """begin; insert into outdoor_env (address, db_time, uptime_ms, bmp085_temp_decic, bmp085_press_pa, batt_mv, panel_mv, apogee_mv, apogee_w_m2) values (%(address)s, now(), %(uptime_ms)s, %(bmp085_temp_decic)s, %(bmp085_press_pa)s, %(batt_mv)s, %(panel_mv)s, %(apogee_mv)s, %(apogee_w_m2)s); commit;"""

print time.strftime(time_fmt),
print "starting..."

while True:
    try:
        values_str = xbee.wait_read_frame()['rf_data']
        print time.strftime(time_fmt),
        print values_str
        sys.stdout.flush()
#	logging will happen later
#        cur.execute("""begin; insert into outdoor_env_binary_log (db_time, rf_data) values (now(), %s); commit;""", [buffer(values_str)])
        values = json.loads(values_str)
        for field in ['apogee_mv', 'apogee_w_m2', 'address', 
                      'uptime_ms', 'bmp085_temp_decic', 
                      'bmp085_press_pa', 'batt_mv', 'panel_mv']:
            values.setdefault(field, None)
        if values.has_key('addr') and values['addr'] == 13:
            cur.execute("""begin; insert into greenbox (addr, db_time, up_ms, bmp_c, bmp_pa, sht_pct, ds20_c, tsl_m2, solar_v, shunt_mv, solar_ma, batt_v, batt_mv, batt_ma) values (%(addr)s, now(), %(up_ms)s, %(bmp_c)s, %(bmp_pa)s, %(sht_pct)s, %(ds20_c)s, %(tsl_m2)s, %(solar_v)s, %(shunt_mv)s, %(solar_ma)s, %(batt_v)s, %(batt_mv)s, %(batt_ma)s); commit;""", values)
            continue
#        cur.execute(insert_query, values)
    except:
        print time.strftime(time_fmt),
        print "ser.close()"
        ser.close()
        cur.close()
        conn.close()
        raise
