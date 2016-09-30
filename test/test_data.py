import serial
import time

data = "\x7e\x00\x16\x90\x00\x7d\x33\xa2\x00\x40\xe6\x4b\x5e\x03\xfd\x01\x00\x00\xff\xff\xf0\xfa\x23\x00\x2b\x02\xb2"

port = raw_input("Please enter your serial port path/name: ")

try:
    ser = serial.Serial(port, 9600)
except serial.serialutil.SerialException as e:
    print "Serial Error: ", e
    sys.exit(1)


while(True):
	ser.write(data)
	print 'Wrote data to serial hopefully'
	time.sleep(5)
