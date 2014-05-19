#!/usr/bin/env python

import json
import re
import struct
import pprint
import traceback
import sys
import time

class PacketDecoder:
	def __init__(self):
		self.log_file = open("ControlTower.log", "a")
			
		self.invalid_id_pattern = re.compile('[^0-9A-Za-z_]')
		self.status = True
		self.decoders = { 
			8827: self.decode_json,          # '{"' -> 8827
			0: self.decode_0,
			1: self.decode_1,
			3: self.decode_3,				 # Schema added by Kenny and Sean in Februrary 2014
			5: self.decode_5,				 # Health packet format
			6: self.decode_6				 # Text packet
		}
		self.time_fmt = '%FT%T %z'

	# Check what the schema number is and return it 
	def check_schema(self, rf_data):
		schema = struct.unpack('<H', rf_data[0:2])[0]
		# print "DEBUG Decoder number: " + str(schema)
		return str(schema)

	def decode(self, rf_data):
		schema = struct.unpack('<H', rf_data[0:2])[0]
		try:
			f = self.decoders[schema]
		except KeyError:
			raise ValueError, 'unrecognized schema: ' + str(schema)
		return f(rf_data)

	def decode_json(self, s):
		return [{'time_offset_s': 0, 'values': json.loads(s)}]

	# ===================================
	#		SCHEMA 5
	#
	#		This schema is for health data.
	#
	# ===================================
	def unpack_5(self,s):
		struct_fmt = '<HHIH'
		values_list = struct.unpack(struct_fmt, s)
		values = {}
		for key, start, end in [('address', 1, 2),
								('uptime_ms', 2, 3),
								('batt_mv', 3, 4),
								]:
			values[key] = values_list[start:end]
			if len(values[key]) == 1:
				values[key] = values[key][0]
		return values;
	
	def decode_5(self,s):
		values_list = self.unpack_5(s)
		values = {}
		print time.strftime(self.time_fmt) + " " + str(values_list)
		return [{'time_offset_s': 0,
				 'values': values_list}]

	# ===================================
	#		SCHEMA 6
	#
	#		This schema is for text data. We can transmit a max of 
	#		80 or so bytes using the Xbee API mode, but we can go 
	# 		ahead and use UP to that amount.
	# ===================================

	def unpack_6(self,s):
		size = len(s)
		struct_fmt = '<' + 'H' + 'c'*(size-2)
		values_list = struct.unpack(struct_fmt, s)
		values_list = list(values_list)
		values_list.pop(0);
		debug_text = ''.join(values_list)
		return debug_text;
	
	def decode_6(self,s):
		debug_msg = str(self.unpack_6(s))
		logstr = time.strftime(self.time_fmt)
		logstr = logstr + "\t Received text data:" + debug_msg + "\n"
		logstr = logstr.replace("\x00", "")
		self.log_file.write(logstr)
		print time.strftime(self.time_fmt) + " " + debug_msg

		# print "TEXT:" + text

	# ===================================
	#		SCHEMA 4
	# ===================================
	def unpack_4(self, s):
		struct_fmt = '<HHIB' + 'H'*15 + 'H'*15 + 'IhH' + 'h'*60 + 'BBBBBBBiii'
		values_list = struct.unpack(struct_fmt, s)
		values = {}
		for key, start, end in [('schema', 0, 1),
								('address', 1, 2), ('uptime_ms', 2, 3),
								('n', 3, 4),
								('batt_mv', 4, 19),
								('panel_mv', 19, 34),
								('bmp085_press_pa', 34, 35),
								('bmp085_temp_decic', 35, 36),
								('humidity_centi_pct', 36, 37),
								('apogee_w_m2', 37, 97),
								('gps_valid_sats', 97, 98),
								('gps_year', 98, 99), ('gps_month', 99, 100),
								('gps_day', 100, 101),
								('gps_hour', 101, 102),
								('gps_minute', 102, 103),
								('gps_second', 103, 104),
								('gps_lat', 104, 105),
								('gps_lon', 105, 106),
								('gps_elev', 106, 107)
								]:
			values[key] = values_list[start:end]
			if len(values[key]) == 1:
				values[key] = values[key][0]
		return values

	def decode_4(self, s):
		p = self.unpack_1(s)

		time_series = []

		n = p['n']            # number of data points in this packet 1..60

		for i in xrange(n-1, -1, -1):
			query_values = {'address': p['address']}

			# values included in the *last* sample of a packet
			if i == n-1:
				query_values['uptime_ms'] = p['uptime_ms']
				query_values['bmp085_press_pa'] = p['bmp085_press_pa']
				query_values['bmp085_temp_decic'] = p['bmp085_temp_decic']
				query_values['humidity_centi_pct'] = p['humidity_centi_pct']

			# subtract n - i - 1 from now() to get this datum's db_time
			# offset that will be used in the insertion query
			time_offset_s = -(n - i - 1)

			# values included in *every* sample of a packet
			query_values['apogee_w_m2'] = p['apogee_w_m2'][i]

			# values included every couple samples of a packet
			if (i+1) % 4 == 0 or i == n-1:
				query_values['batt_mv'] = p['batt_mv'][i/4]
				query_values['panel_mv'] = p['panel_mv'][i/4]

			time_series.append({'time_offset_s': time_offset_s,
							'values': query_values})

		return time_series

	def unpack_1(self, s):
		struct_fmt = '<HHIB' + 'H'*15 + 'H'*15 + 'IhH' + 'h'*60 + 'BBBBBBBiii'
		values_list = struct.unpack(struct_fmt, s)
		values = {}
		for key, start, end in [('schema', 0, 1),
								('address', 1, 2),
								('uptime_ms', 2, 3), ('n', 3, 4),
								('batt_mv', 4, 19),
								('panel_mv', 19, 34),
								('bmp085_press_pa', 34, 35),
								('bmp085_temp_decic', 35, 36),
								('humidity_centi_pct', 36, 37),
								('apogee_w_m2', 37, 97),
								('gps_valid_sats', 97, 98),
								('gps_year', 98, 99),
								('gps_month', 99, 100),
								('gps_day', 100, 101),
								('gps_hour', 101, 102),
								('gps_minute', 102, 103),
								('gps_second', 103, 104),
								('gps_lat', 104, 105),
								('gps_lon', 105, 106),
								('gps_elev', 106, 107)
								]:
			values[key] = values_list[start:end]
			if len(values[key]) == 1:
				values[key] = values[key][0]
		return values

	def decode_1(self, s):
		p = self.unpack_1(s)

		time_series = []

		n = p['n']            # number of data points in this packet 1..60

		for i in xrange(n-1, -1, -1):
			query_values = {'address': p['address']}

			# values included in the *last* sample of a packet
			# This is a special case statement to take care of this. 
			# If you only need to sample one thing, include this here, since the
			# code in the arduino will sample and overwrite until the last sample. 
			if i == n-1:
				query_values['uptime_ms'] = p['uptime_ms']
				query_values['bmp085_press_pa'] = p['bmp085_press_pa']
				query_values['bmp085_temp_decic'] = p['bmp085_temp_decic']
				query_values['humidity_centi_pct'] = p['humidity_centi_pct']

			# subtract n - i - 1 from now() to get this datum's db_time
			# offset that will be used in the insertion query
			time_offset_s = -(n - i - 1)

			# values included in *every* sample of a packet
			query_values['apogee_w_m2'] = p['apogee_w_m2'][i]

			# values included every couple samples of a packet
			if (i+1) % 4 == 0 or i == n-1:
				query_values['batt_mv'] = p['batt_mv'][i/4]
				query_values['panel_mv'] = p['panel_mv'][i/4]

			time_series.append({'time_offset_s': time_offset_s,
							'values': query_values})
		return time_series


	# ===================================
	#		SCHEMA 3
	# ===================================
	def unpack_3(self, s):
		struct_fmt = '<HHIB' + 'H'*6 + 'H'*6 + 'IHH' + 'H'*20
		values_list = struct.unpack(struct_fmt, s)
		values = {}
		for key, start, end in [('schema', 0, 1),
								('address', 1, 2),
								('uptime_ms', 2, 3),
								('overflow_num', 3, 4),
								('n', 4, 5),
								('batt_mv', 5, 11),
								('panel_mv', 11, 17),
								('bmp085_press_pa', 17, 18),
								('bmp085_temp_decic', 18, 19),
								('humidity_centi_pct', 19, 20),
								('apogee_w_m2', 20, 99),
								]:
			values[key] = values_list[start:end]
			if len(values[key]) == 1:
				values[key] = values[key][0]
			print str(values)
		return values

	def decode_3(self, s):
		p = self.unpack_3(s)

		time_series = []

		n = p['n']            # number of data points in this packet 1..60

		try:
			for i in xrange(n-1, -1, -1):
				query_values = {'address': p['address']}

				# values included in the *last* sample of a packet
				# This is a special case statement to take care of this. 
				# If you only need to sample one thing, include this here, since the
				# code in the arduino will sample and overwrite until the last sample. 
				if i == n-1:
					query_values['uptime_ms'] = p['uptime_ms']
					query_values['overflow_num'] = p['overflow_num']
					query_values['bmp085_press_pa'] = p['bmp085_press_pa']
					query_values['bmp085_temp_decic'] = p['bmp085_temp_decic']
					query_values['humidity_centi_pct'] = p['humidity_centi_pct']

				# subtract n - i - 1 from now() to get this datum's db_time
				# offset that will be used in the insertion query
				time_offset_s = -(n - i - 1)

				# values included in *every* sample of a packet
				# The values here should not have any division done. 
				# Example:
				# 	query_values['apogee_w_m2'] = p['apogee_w_m2'][i]

				# values included every couple samples of a packet	
				# be sure to modify if cases to take care of this. 
				if (i+1) % 3 == 0 or i == n-1:
					query_values['apogee_w_m2'] = p['apogee_w_m2'][i/3]

				if (i+1) % 10 == 0 or i == n-1:
					query_values['batt_mv'] = p['batt_mv'][i/10]
					query_values['panel_mv'] = p['panel_mv'][i/10]

				# Append the offset so that we can package the db query later
				time_series.append({'time_offset_s': time_offset_s,
								'values': query_values})
		except Exception, err:
			print traceback.format_exc()

		return time_series


	# ===================================
	#		Schema 0
	# ===================================
	def decode_0(self, s):
		struct_fmt = '<HHLhLHHHH'
		values_list = struct.unpack(struct_fmt, s)
		values = {}
		for key, offset in [('address', 1),
							('uptime_ms', 2),
							('bmp085_temp_decic', 3),
							('bmp085_press_pa', 4),
							('batt_mv', 5),
							('panel_mv', 6),
							('apogee_mv', 7),
							('apogee_w_m2', 8)
							]:
			values[key] = values_list[offset]

		return [{'time_offset_s': 0,
				 'values': values}]

	def create_query(self, v):
		columns = sorted(v['values'].keys())
		for c in columns:
			if re.search(self.invalid_id_pattern, c):
				raise ValueError, 'column name contains invalid character(s): ' + c
		column_names = ', '.join(columns)
		placeholders = ', '.join(['%(' + x + ')s' for x in columns])
		return '''INSERT INTO outdoor_env (db_time, %s) VALUES (now() + '%s seconds'::interval, %s)''' % (column_names, v['time_offset_s'], placeholders)

	def create_query_debug(self, v):
		columns = sorted(v['values'].keys())
		for c in columns:
			if re.search(self.invalid_id_pattern, c):
				raise ValueError, 'column name contains invalid character(s): ' + c
		column_names = ', '.join(columns)
		placeholders = ', '.join(['%(' + x + ')s' for x in columns])
		return '''INSERT INTO outdoor_health (db_time, %s) VALUES (now() + '%s seconds'::interval, %s)''' % (column_names, v['time_offset_s'], placeholders)

	def create_query_health(self, v):
		columns = sorted(v['values'].keys())
		for c in columns:
			if re.search(self.invalid_id_pattern, c):
				raise ValueError, 'column name contains invalid character(s): ' + c
		column_names = ', '.join(columns)
		placeholders = ', '.join(['%(' + x + ')s' for x in columns])
		return '''INSERT INTO outdoor_env_health (db_time, %s) VALUES (now() + '%s seconds'::interval, %s)''' % (column_names, v['time_offset_s'], placeholders)
