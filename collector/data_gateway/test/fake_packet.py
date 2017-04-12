import sys
import serial
import binascii

try:
    ser = serial.Serial('/dev/ttyUSB0', 9600)
except serial.serialutil.SerialException as e:
    print "Serial Error: ", e
    sys.exit(1)
ser.flushInput()
ser.flushOutput()

#	this denotes the start of the first block
f = open('test_data','w')
while True:
	var = ser.read()
	asc = ord(var)
	print str(asc)
	f.write(str(asc) + '\n')
f.close()	
#	this denotes the end of the first block

"""

#	this denotes the start of the second block
f = open('test_data', 'r')
g = open('packet_data' , 'w')
for line in f:
	packet_data = hex(int(line.rstrip())) 
	print packet_data
	g.write(packet_data + '\n')
	#print binascii.a2b_hqx(str(asc))
g.close()
f.close()
#	this denotes the end of the second block
"""
