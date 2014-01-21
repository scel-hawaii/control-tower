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

	def __init__(self):
		self.time_fmt = '%FT%T %z'
		self.reis_decoder = PacketDecoder()
		self.init_db_connection()
		self.init_uart_connection()

	def init_db_connection(self):
		try:
			self.conn = psycopg2.connect(host="127.0.0.1")
			self.cur = self.conn.cursor()
		except:
			print "Something went wrong with the database."

	def init_uart_connection(self):
		#try:
			#ser = Serial(sys.argv[1], 9600)
		#except IndexError:
				#ser = Serial('/dev/ttyUSB0', 9600)

		self.ser = Serial('/dev/ttyUSB0', 9600)
		self.xbee = ZigBee(self.ser, escaped=True)

	def start_polling(self, option = "DATABASE"):
		if option == "DATABASE":
			self.poll_to_db()
		else:
			self.poll_to_screen_blank()

	def poll_to_screen(self):
		print time.strftime(self.time_fmt),
		print "starting..."

		while True:
			try:
				rf_data = self.xbee.wait_read_frame()['rf_data']
				print
				print
				print time.strftime(self.time_fmt)
				print rf_data
				try:
					time_points = self.reis_decoder.decode(rf_data)
					for t in time_points:
						print
						print 'time offset:', t['time_offset_s']
						print 'values:', t['values']
				except Exception as e:
					print 'exception:', str(e)
				sys.stdout.flush()
			except:
				print time.strftime(self.time_fmt),
				print "self.ser.close()"
				self.ser.close()
				raise
	def poll_to_screen_blank(self):
		while True:
			rf_data = self.xbee.wait_read_frame()['rf_data']
			print
			print
			print time.strftime(self.time_fmt)
			print rf_data


	def poll_to_db(self):
		print time.strftime(self.time_fmt),
		print "starting..."

		while True:
			try:
				rf_data = self.xbee.wait_read_frame()['rf_data']

				try:
					self.cur.execute('BEGIN;')
					for t in self.reis_decoder.decode(rf_data):
						self.cur.execute(self.reis_decoder.create_query(t), t['values'])
					self.cur.execute('COMMIT;')
				except Exception, e:
					self.cur.execute('ROLLBACK;')
					self.cur.execute('BEGIN;')
					self.cur.execute(
						'''INSERT INTO outdoor_env_unrecognized (db_time, rf_data, exception) VALUES (now(), %s, %s);''',
						[buffer(rf_data), str(sys.exc_info()[0]) + ': ' + str(e)])
					self.cur.execute('COMMIT;')
					continue

			except:
				print time.strftime(self.time_fmt),
				print "stopping!"
				self.ser.close()
				self.cur.close()
				self.conn.close()
				raise

if __name__ == "__main__":
	test = CoordinatorReceiver()
	test.start_polling("DATABASE")
