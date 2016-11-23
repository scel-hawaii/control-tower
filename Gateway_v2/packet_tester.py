from xbee import ZigBee
import sys
import serial
import datetime
import struct
import collections
import threading

from decoder import Decoder
from xbee_gateway import XBeeGateway

decoder = Decoder()
xbg = XBeeGateway()

decoder.register_callback(decoder.print_dictionary)
decoder.register_callback(decoder.write_to_file)
#decoder.register_callback(decoder.write_to_db)
xbg.register_callback(decoder.decode_data)


port = raw_input("Please enter your serial port path/name: ")
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
