
'''
	def decode_3(self, s):
		unpacked_data = self.unpack_3(s);
		time_series = []
		print "Cool unpacked data"
		print unpacked_data
		n = unpacked_data['n']            # number of data points in this packet 1..60

		# Leave the address in with each packet
		query_values = {'address': unpacked_data['address']}
		print "Here we are outside the xrange loop"

		for i in xrange(n-1, -1, -1):
			print "Here we are INSIDE the xrange loop"

			# values included in the *last* sample of a packet
			#if i == n-1:
				# query_values['apogee_w_m2'] = unpacked_data['apogee_w_m2']
				# query_values['uptime_ms'] = p['uptime_ms']
				# query_values['bmp085_press_pa'] = p['bmp085_press_pa']
				# query_values['bmp085_temp_decic'] = p['bmp085_temp_decic']
				# query_values['humidity_centi_pct'] = p['humidity_centi_pct']

			# subtract n - i - 1 from now() to get this datum's db_time
			# offset that will be used in the insertion query
			print "Here we are before the time_offset_calc"
			time_offset_s = -(n - i - 1)
			print "Here we are AFTER the time_offset_calc"
			print time_offset_s

			print "Here we are before apogee sample"
			# values included in *every* sample of a packet
			print unpacked_data['apogee_w_m2']
			print "i = " + i 
			print unpacked_data['apogee_w_m2'][i]
			query_values['apogee_w_m2'] = unpacked_data['apogee_w_m2'][i]
			print "Here we are AFTER apogee sample"

			# values included every couple samples of a packet
			if (i+1) % 4 == 0 or i == n-1:
				query_values['batt_mv'] = unpacked_data['batt_mv'][i/6]
				query_values['panel_mv'] = unpacked_data['panel_mv'][i/6]

			print "Here we are before the append"
			time_series.append({'time_offset_s': time_offset_s,
							'values': query_values})
			print "Here we are AFTER the append"
			print "Finished with the time series"
			print time_series
		return time_series
'''
