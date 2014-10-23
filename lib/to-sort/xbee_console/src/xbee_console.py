########################################################
#
#		An Xbee Console Written in Python
#
########################################################
import serial
import time
import struct
from xbee import ZigBee

serial_port = serial.Serial('/dev/ttyUSB0', 9600)
xbee = ZigBee(serial_port, escaped=True)

# Send a command 
xbee.send("at", frame='A', command='MY')

# Wait for the response
result = xbee.wait_read_frame()['parameter']

# Parase and print the result
output = struct.unpack('<bb', result)
print output

serial_port.close()
