#!/usr/bin/env python

import json
import re
import struct

class PacketDecoder:
	invalid_id_pattern = re.compile('[^0-9A-Za-z_]')
	def __init__(self):
		self.status = True

	def decode(self, rf_data):
		schema = struct.unpack('<H', rf_data[0:2])[0]
		try:
			f = decoders[schema]
		except KeyError:
			raise ValueError, 'unrecognized schema: ' + str(schema)
		return f(rf_data)

	def decode_json(self, s):
		return [{'time_offset_s': 0, 'values': json.loads(s)}]

	def unpack_1(self, s):
		struct_fmt = '<HHIB' + 'H'*15 + 'H'*15 + 'IhH' + 'h'*60 + 'BBBBBBBiii'
		values_list = struct.unpack(struct_fmt, s)
		values = {}
		for key, start, end in [('schema', 0, 1),
								('address', 1, 2),
								('uptime_ms', 2, 3),
								('n', 3, 4),
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
		p = unpack_1(s)

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
			if re.search(invalid_id_pattern, c):
				raise ValueError, 'column name contains invalid character(s): ' + c
		column_names = ', '.join(columns)
		placeholders = ', '.join(['%(' + x + ')s' for x in columns])
		return '''INSERT INTO outdoor_env (db_time, %s) VALUES (now() + '%s seconds'::interval, %s)''' % (column_names, v['time_offset_s'], placeholders)

	decoders = {
		8827: decode_json,          # '{"' -> 8827
		0: decode_0,
		1: decode_1
		}

