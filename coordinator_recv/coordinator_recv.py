#!/usr/bin/env python

# Library Imports
from xbee import ZigBee
from serial import Serial
import psycopg2
import json
import sys
import time

# Local imports
from decode import PacketDecoder

DATABASE = 1 

class CoordinatorReceiver:
	time_fmt = '%FT%T %z'
	reis_decoder = PacketDecoder()

	def __init__(self):
		self.init_db_connection()
		self.init_uart_connection()

	def init_db_connection(self):
		try:
			conn = psycopg2.connect(host="127.0.0.1")
			cur = conn.cursor()
		except:
			print "Something went wrong with the database."

	def init_uart_connection(self):
		try:
			ser = Serial(sys.argv[1], 9600)
		except IndexError:
				ser = Serial('/dev/ttyUSB0', 9600)

		xbee = ZigBee(ser, escaped=True)

	def start_polling(option = DATABASE):
		if option == DATABASE:
			poll_to_db()
		else:
			poll_to_screen()

	def poll_to_screen(self):
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
					time_points = reis_decoder.decode(rf_data)
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

	def poll_to_db(self):
		print time.strftime(time_fmt),
		print "starting..."

		while True:
			try:
				rf_data = xbee.wait_read_frame()['rf_data']

				try:
					cur.execute('BEGIN;')
					for t in reis_decoder.decode(rf_data):
						cur.execute(reis_decoder.create_query(t), t['values'])
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

if __name__ == "__main__":
	test = CoordinatorReceiver()
