import serial
import time

heartbeat = "\x7e\x00\x16\x90\x00\x7d\x33\xa2\x00\x40\xe6\x4b\x5e\x03\xfd\x01\x00\x00\xff\xff\xf0\xfa\x23\x00\x2b\x02\xb2"
apple = "\x7e\x00\x22\x90\x00\x7d\x33\xa2\x00\x40\x9f\x27\xa7\x29\x6c\x01\x01\x00\x65\x00\x80\x6f\x69\x3d\x06\x0f\x71\x7d\x33\x5a\x8a\x01\x00\x76\x01\x22\x00\x6e\x09\xee"

port = raw_input("Please enter your serial port path/name: ")

try:
    ser = serial.Serial(port, 9600)
except serial.serialutil.SerialException as e:
    print "Serial Error: ", e
    sys.exit(1)

heartbeatFlag = True
while(True):
	if heartbeatFlag:
		ser.write(heartbeat)
		heartbeatFlag = False
	else:
		ser.write(apple)
		heartbeatFlag = True

	print 'Wrote data to serial hopefully'
	time.sleep(5)
