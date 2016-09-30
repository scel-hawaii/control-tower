from xbee import ZigBee
import sys
import serial
import datetime
import struct
import collections

from decoder import Decoder

decoder = Decoder()
port = raw_input("Please enter your serial port path/name: ")

try:
    ser = serial.Serial(port, 9600)
    xbee = ZigBee(ser, escaped=True)
except serial.serialutil.SerialException as e:
    print "Serial Error: ", e
    sys.exit(1)

print "Start Program."

while True:

	#read xbee data
	f = xbee.wait_read_frame()
	data = f['rf_data']
	dlen = len(data)
	timestamp = datetime.datetime.now()
	print str(timestamp) + " Got a packet of length " + str(dlen)

	decoder.decode_data(data, decoder.print_dictionary)	
