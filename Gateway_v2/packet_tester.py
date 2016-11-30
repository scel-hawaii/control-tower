from xbee import ZigBee
import sys
import serial
import datetime
import struct
import collections
import threading

from decoder import Decoder
from xbee_gateway import XBeeGateway

args = sys.argv

decoder = Decoder()
xbg = XBeeGateway()

decoder.register_callback(decoder.print_dictionary)
decoder.register_callback(decoder.write_to_file)
decoder.register_callback(decoder.write_to_db)
xbg.register_callback(decoder.decode_data)

# if we have no special arguments
if len(args) == 1:
	# port can be accessed by /dev/serial/by-id/<device name> as opposed to /dev/tty/USB0. The latter will never change
	# use the line of code below when running simulation to manually enter port
	port = raw_input("Please enter your serial port path/name: ")

# if we want to automatically get the port...
elif args[1] == 'auto' or args[1] == 'a':
	print 'Automatically setting port for USB FTDI Device'
	# set port to usb FTDI Device
	port = '/dev/serial/by-id/usb-FTDI_FT231X_USB_UART_DN01DBGI-if00-port0'
# we have no extra args 
# we have confusing arguments
else:
	# quit the program
	print 'Error, Invalid arguments'
	sys.exit()

baud_rate = 9600
t_flag = threading.Event()
kill_flag = threading.Event()
while True:
	currentTime = datetime.datetime.now()
	# log start times to file
        fileName = 'reset_log.txt'
	with open(fileName, 'a') as logfile:
        	logfile.write(str(currentTime))
		logfile.write('\n')

	kill_flag.clear()
	t_flag.set()

	xbg.setup_xbee(port, baud_rate)
	newThread = threading.Thread(target=xbg.begin_test, args=(1,t_flag,kill_flag))
	newThread.daemon = True
	newThread.start()

	while t_flag.is_set():
		t_flag.clear()
		#sleep 30 seconds then check to see if we have received anything
		t_flag.wait(60)

	kill_flag.set()
