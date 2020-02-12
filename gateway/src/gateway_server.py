#!/usr/bin/env python
# This script is the main gateway server

from xbee import ZigBee
import sys
import os
import serial
import datetime
import struct
import collections
import threading

from decoder import Decoder
from xbee_gateway import XBeeGateway

args = sys.argv

port = ""
# if we have no special arguments
if len(args) == 2:
	# port can be accessed by /dev/serial/by-id/<device name> as opposed to /dev/tty/USB0. The latter will never change
	# use the line of code below when running simulation to manually enter port
	# port = raw_input("Please enter your serial port path/name: ")
    #
    #
    # Note from Kenny:
    #   The best way I have to find out the device id currently is to go to the /dev/serial/by-id folder
    #   and then see if a new device shows up after I plug in a device.
    #
    port = sys.argv[1]

# if we want to automatically get the port...
elif args[1] == 'auto' or args[1] == 'a':
	print 'Automatically setting port for USB FTDI Device'
	# set port to usb FTDI Device
	port = '/dev/serial/by-id/usb-FTDI_FT231X_USB_UART_DN01DBGI-if00-port0'

# we have no extra args
# we have confusing arguments
else:
    print 'Attempting to automatically setting port for USB FTDI Device'
    port = ""
    serial_ports = os.listdir('/dev/serial/by-id/')
    if len(serial_ports) == 0:
        print("ERROR: there were are no connected serial ports")
        sys.exit(1)
    elif len(serial_ports) > 1:
        print("ERROR: there are too many connected serial ports, cannot determine the correct port.")
        print("You have to manually specify the port... here are your options:")
        for serial_port in serial_ports:
            print(os.path.join("/dev/serial/by-id", serial_port))
        sys.exit(1)
    else:
        port = os.path.join("/dev/serial/by-id", serial_ports[0])
        print(serial_ports)

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

	# setup decoder and xbee device
	decoder = Decoder()
	xbg = XBeeGateway()

	decoder.register_callback(decoder.print_dictionary)
	decoder.register_callback(decoder.write_to_file)
	# decoder.register_callback(decoder.write_to_db)
	xbg.register_callback(decoder.decode_data)

	xbg.setup_xbee(port, baud_rate)
	xbg.begin_test(1,t_flag,kill_flag)
	#newThread = threading.Thread(target=xbg.begin_test, args=(1,t_flag,kill_flag))
	#newThread.daemon = True
	#newThread.start()

	#while t_flag.is_set():
		#t_flag.clear()
		#sleep 30 seconds then check to see if we have received anything
		#t_flag.wait(60)

	#kill_flag.set()
