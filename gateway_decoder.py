from xbee import ZigBee
import sys
import serial
import datetime
import struct
import collections


schemaDict = {
	'ga_legacy': 'HHBI'+'B'+'H'*6+'H'*6+'IhH'+'H'*20,
	'0': 'HHIH', #Heartbeat schema
	'1': 'HHIHHIhHH',	#Apple schema
	'2': 'HHIHHHhHH', #Cranberry schema
	'3': 'HHIHHIhHH'
	}
port = raw_input("Please enter your serial port path/name: ")

try:
    ser = serial.Serial(port, 9600)
    xbee = ZigBee(ser, escaped=True)
except serial.serialutil.SerialException as e:
    print "Serial Error: ", e
    sys.exit(1)

print "Start Program."

while True:
	valid = 0

	#read xbee data
	f = xbee.wait_read_frame()
	data = f['rf_data']
	dlen = len(data)
	timestamp = datetime.datetime.now()
	print str(timestamp) + " Got a packet of length " + str(dlen)
	
	#check if schema is valid
	schema = struct.unpack('<' + 'H', data[0:2])[0]
	for key in schemaDict:
		if str(schema) == key:
			valid = 1		
			break

	if valid: 
	
		#create format. Refer to documentation on python struct
		fmt = '<' + schemaDict[str(schema)]
		
		dataDict = {}

		if schema == 1:	#apple schema
			dataDict["schema"] = struct.unpack('<' + 'H', data[0:2])[0]
			dataDict["node_addr"] = struct.unpack('<' + 'H', data[2:4])[0]
			dataDict["uptime_ms"] = struct.unpack('<' + 'I', data[4:8])[0]
			dataDict["batt_mv"] = struct.unpack('<' + 'H', data[8:10])[0]
			dataDict["panel_mv"] = struct.unpack('<' + 'H', data[10:12])[0]
			dataDict["press_pa"] = struct.unpack('<' + 'I', data[12:16])[0]
			dataDict["temp_c"] = struct.unpack('<' + 'h', data[16:18])[0]
			dataDict["humidity_centi_pct"] = struct.unpack('<' + 'H', data[18:20])[0]
			dataDict["apogee_w_m2"] = struct.unpack('<' + 'H', data[20:22])[0]

		elif schema == 2: #cranberry schema
			dataDict["schema"] = struct.unpack('<' + 'H', data[0:2])[0]
			dataDict["node_addr"] = struct.unpack('<' + 'H', data[2:4])[0]
			dataDict["uptime_ms"] = struct.unpack('<' + 'I', data[4:8])[0]
			dataDict["batt_mv"] = struct.unpack('<' + 'H', data[8:10])[0]
			dataDict["panel_mv"] = struct.unpack('<' + 'H', data[10:12])[0]
			dataDict["apogee_w_m2"] = struct.unpack('<' + 'H', data[12:14])[0]
			dataDict["temp_c"] = struct.unpack('<' + 'h', data[14:16])[0]
			dataDict["humidity_centi_pct"] = struct.unpack('<' + 'H', data[16:18])[0]
			dataDict["press_kpa"] = struct.unpack('<' + 'H', data[18:20])[0]
		
		elif schema == 3: #dragonfruit schema
			dataDict["schema"] = struct.unpack('<' + 'H', data[0:2])[0]
			dataDict["node_addr"] = struct.unpack('<' + 'H', data[2:4])[0]
			dataDict["uptime_ms"] = struct.unpack('<' + 'I', data[4:8])[0]
			dataDict["batt_mv"] = struct.unpack('<' + 'H', data[8:10])[0]
			dataDict["panel_mv"] = struct.unpack('<' + 'H', data[10:12])[0]
			dataDict["press_pa"] = struct.unpack('<' + 'I', data[12:16])[0]	
			dataDict["temp_c"] = struct.unpack('<' + 'h', data[16:18])[0]
			dataDict["humidity_centi_pct"] = struct.unpack('<' + 'H', data[18:20])[0]
			dataDict["apogee_w_m2"] = struct.unpack('<' + 'H', data[20:22])[0]
			
		elif schema == 0: #heartbeat schema
			dataDict["schema"] = struct.unpack('<' + 'H', data[0:2])[0]
			dataDict["node_addr"] = struct.unpack('<' + 'H', data[2:4])[0]
			dataDict["uptime_ms"] = struct.unpack('<' + 'I', data[4:8])[0]
			dataDict["batt_mv"] = struct.unpack('<' + 'H', data[8:10])[0]

		#sort alphabetically & display 
		orderedData = collections.OrderedDict(sorted(dataDict.items()))
		for key, value in orderedData.iteritems():
			print key + ": " + str(value)

	else:
		print "Not A Valid Packet"
	
