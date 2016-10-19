import sys
import serial
import binascii

try:
    ser = serial.Serial('/dev/cu.usbserial-DN01DS4M', 9600)
except serial.serialutil.SerialException as e:
    print "Serial Error: ", e
    sys.exit(1)
ser.flushInput()
ser.flushOutput()

f = open('test_data','w')
while True:
	var = ser.read()
	asc = ord(var)
	print str(asc)
	f.write(str(asc) + '\n')
f.close()	
f = open('test_data', 'r')
for line in f:
	print hex(int(line.rstrip()))
	#print binascii.a2b_hqx(str(asc))
