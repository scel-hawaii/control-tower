from xbee import ZigBee
import sys
import serial
import datetime
import struct
import collections

schemaDict = {'ga_legacy': 'HHBI'+'B'+'H'*6+'H'*6+'IhH'+'H'*20,
	      '0': 'HHI'+'H'+'H'+'I'+'h'+'H'+'H',	#Apple schema
		  '5': 'HHIH'	#Apple Heartbeat schema
		  }

try:
    ser = serial.Serial('/dev/cu.usbserial-DN01DS4M', 9600)
    xbee = ZigBee(ser, escaped=True)
except serial.serialutil.SerialException as e:
    print "Serial Error: ", e
    sys.exit(1)

print "Start Program."

while True:
	valid = 0;
	f = xbee.wait_read_frame()
	data = f['rf_data']
	dlen = len(data)
	timestamp = datetime.datetime.now()

	print str(timestamp) + " Got a packet of length " + str(dlen)

	schema = struct.unpack('<' + 'H', data[0:2])[0];


	for key in schemaDict:
		if str(schema) == key:
			valid = 1;		
			break

	if valid:
	
		fmt = '<' + schemaDict[str(schema)]
		#unpacked = struct.unpack(fmt, someString)
		#print unpacked
		dataDict = {}

		if schema == 0:	#if apple schema
			dataDict["schema"] = struct.unpack('<' + 'H', data[0:2])[0];
			dataDict["node_addr"] = struct.unpack('<' + 'H', data[2:4])[0];
			dataDict["uptime_ms"] = struct.unpack('<' + 'I', data[4:8])[0];
			dataDict["batt_mv"] = struct.unpack('<' + 'H', data[8:10])[0];
			dataDict["panel_mv"] = struct.unpack('<' + 'H', data[10:12])[0];
			dataDict["press_pa"] = struct.unpack('<' + 'I', data[12:16])[0];
			dataDict["temp_c"] = struct.unpack('<' + 'h', data[16:18])[0];
			dataDict["humidity_centi_pct"] = struct.unpack('<' + 'H', data[18:20])[0];
			dataDict["apogee_w_m2"] = struct.unpack('<' + 'H', data[20:22])[0];

		elif schema == 5: #if apple heartbeat schema
			dataDict["schema"] = struct.unpack('<' + 'H', data[0:2])[0];
			dataDict["node_addr"] = struct.unpack('<' + 'H', data[2:4])[0];
			dataDict["uptime_ms"] = struct.unpack('<' + 'I', data[4:8])[0];
			dataDict["batt_mv"] = struct.unpack('<' + 'H', data[8:10])[0];

		orderedData = collections.OrderedDict(sorted(dataDict.items()))
		for key, value in orderedData.iteritems():
			print key + ": " + str(value)

	else:
		print "Not A Valid Packet"
	##	fmt = '<' + 'HHI' + 'H'*6 + 'H'*6  + 'IhH' + 'H'*20
		#break
	##	parsed = struct.unpack(fmt, data)
	 #       print str(parsed)
