#!/usr/bin/env python

#	======================================================================
#
#
#	File Name:	coordinator_recv
#	Author: 	Adam Oberbeck
#	Editors:	Kenny Luong, Others
#	
#	Description:
#	
#	This file is the primary server program which takes in data from the 
#   REIS sensing and monitoring (weatherbox) project. For the moment, all 
#	data is sent to this coordinator. 
#
#	TODO: Integrate screen and process management into this file.
#
#	======================================================================

# Library Imports
from xbee import ZigBee
from serial import Serial
import psycopg2
import json
import sys
import time
import argparse

# Local imports
from decode import PacketDecoder

DATABASE = 1 

class CoordinatorReceiver:
	# ---------------------------------------------------------------------
	#
	#	Function Name: __INIT__
	#
	#	The constructor
	# ---------------------------------------------------------------------
	def __init__(self):
		self.init_arg_parse()
		self.time_fmt = '%FT%T %z'
		self.reis_decoder = PacketDecoder()
		self.init_db_connection()
		self.init_uart_connection()
		# TODO: Implement setup for arguments and a help menu (use argparse)

	def init_arg_parse(self):
		parser = argparse.ArgumentParser()
		parser.add_argument('--output')
		parser.add_argument('--mode')
		parser.add_argument('--tty')
		self.args = parser.parse_args()
		# Warn the user that we're using a different mode.
		if self.args.mode:
			print "Warning: Default mode disabled!!!"
			print "\t\t -- " + self.args.mode + " -- mode enabled."
		if self.args.output:
			print "Warning: Manual server select type enabled."
			print "Running with " + self.args.output
		if self.args.tty:
			print "Warning: Manual ttyUSB selected."
			print "Running with " + self.args.tty
	

	# ---------------------------------------------------------------------
	#
	#	Function Name: init_db_connection
	#
	#	This function initalizes the database connection, and assigns 
	#	the cursor to our self.cur object variable.
	# ---------------------------------------------------------------------
	def init_db_connection(self):
		try:
			self.conn = psycopg2.connect(host="127.0.0.1")
			self.cur = self.conn.cursor()
		except:
			print "Something went wrong with the database."

	# ---------------------------------------------------------------------
	#
	#	Function Name: init_uart_connection
	#
	#	This function initalizes the serial connection with the FTDI adapter.
	#	
	# ---------------------------------------------------------------------
	def init_uart_connection(self):
		#try:
			#ser = Serial(sys.argv[1], 9600)
		#except IndexError:
				#ser = Serial('/dev/ttyUSB0', 9600)

		#
		if self.args.tty:
			self.ser = Serial('/dev/' + self.args.tty,57600)
		else:
			self.ser = Serial('/dev/ttyUSB0', 9600)

		self.xbee = ZigBee(self.ser, escaped=True)
	# ---------------------------------------------------------------------
	#
	#	Function Name: start_polling
	#
	#	Starts polling for data, either to the screen or to the database,
	#	depending on what arugments are passed.
	# ---------------------------------------------------------------------
	def start_polling(self, option = "DATABASE"):
		if self.args.output:
			output_mode = self.args.output
			if output_mode == "database":
				self.poll_to_db()
			elif output_mode == "blank":
				self.poll_to_screen_blank()
			elif output_mode == "screen":
				self.poll_to_screen()
			elif output_mode == "address":
				#TODO: This is hardcoded now.. lets fix and add something later
				# to allow the user to put in an address
				self.poll_for_address(114)
			else:
				raise nameError("Incorrect Mode!")
		else:
			self.poll_to_db()

	# ---------------------------------------------------------------------
	#
	#	Function Name: poll_to_screen
	#
	#	This function polls to the screen, printing out the date that the 
	#	data was recieved, as well as the data itself (after parsing).
	# ---------------------------------------------------------------------
	def poll_to_screen(self):
		print time.strftime(self.time_fmt),
		print "starting..."

		while True:
			try:
				rf_data = self.xbee.wait_read_frame()['rf_data']
				print
				print
				print time.strftime(self.time_fmt)
				# print " ".join("{0:x}".format(ord(c)) for c in rf_data)
				try:
					time_points = self.reis_decoder.decode(rf_data)
					#for t in time_points:
						#print
						#print 'time offset:', t['time_offset_s']
						#print 'values:', t['values']
				except Exception as e:
					print 'exception:', str(e)
				sys.stdout.flush()
			except:
				print time.strftime(self.time_fmt),
				print "self.ser.close()"
				self.ser.close()
				raise

	# ---------------------------------------------------------------------
	#
	#	Function Name: poll_for_address
	#
	# 	This function polls for a specific address, and prints out the data 
	# 	if that address arrived or not. Useful for initial connection
	# 	debugging.
	# ---------------------------------------------------------------------
	def poll_for_address(self, address):
		print time.strftime(self.time_fmt),
		print "starting..."

		while True:
			try:
				rf_data = self.xbee.wait_read_frame()['rf_data']
				try:
					time_points = self.reis_decoder.decode(rf_data)
					if( self.find_address(time_points) == address ):
						print "We found it!"
						print time.strftime(self.time_fmt)
					#for t in time_points:
						#print
						#print 'time offset:', t['time_offset_s']
						#print 'values:', t['values']
				except Exception as e:
					print 'exception:', str(e)
				sys.stdout.flush()
			except:
				print time.strftime(self.time_fmt),
				print "self.ser.close()"
				self.ser.close()
				raise

	def find_address(self,time_points):
		return time_points[1]['values']['address']


	# ---------------------------------------------------------------------
	#
	#	Function Name: poll_to_blank
	#
	#	Purely a test function, this function prints out if some data was 
	#	recieved and prints it out.	
	# ---------------------------------------------------------------------
	def poll_to_screen_blank(self):
		while True:
			rf_data = self.xbee.wait_read_frame()['rf_data']
			print
			print
			print time.strftime(self.time_fmt)
			print rf_data


	# ---------------------------------------------------------------------
	#
	#	Function Name: poll_to_db
	#
	#	poll_to_db polls for data, decodes it, and then stuffs it into the
	#	local database.
	# ---------------------------------------------------------------------
	def poll_to_db(self):
		print time.strftime(self.time_fmt),
		print "starting..."

		while True: 
			try:
				rf_data = self.xbee.wait_read_frame()['rf_data']
				packet_schema = int(self.reis_decoder.check_schema(rf_data))
				print "We got a packet of schema: " + str(packet_schema)

				if packet_schema == 6:
					print "CoordinatorDecoder: Print a debug msg!"
					self.reis_decoder.decode(rf_data)

				elif packet_schema == 5:
					print "CoordinatorDecoder: ParseHealth!!"
					try:
						self.cur.execute('BEGIN;')
						print "Yay!"
						for t in self.reis_decoder.decode(rf_data):
							print t
							self.cur.execute(self.reis_decoder.create_query_health(t), t['values'])
						self.cur.execute('COMMIT;')
					except Exception, e:
						self.cur.execute('ROLLBACK;')
						self.cur.execute('BEGIN;')
						self.cur.execute(
							'''INSERT INTO outdoor_env_unrecognized (db_time, rf_data, exception) VALUES (now(), %s, %s);''',
							[buffer(rf_data), str(sys.exc_info()[0]) + ': ' + str(e)])
						self.cur.execute('COMMIT;')
						continue
				else:
					print "CoordinatorDecoder: Parse Data.."
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
	test.start_polling()
