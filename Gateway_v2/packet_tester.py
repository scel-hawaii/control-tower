from xbee import ZigBee
import sys
import serial
import datetime
import struct
import collections

from decoder import Decoder
from xbee_gateway import XBeeGateway

decoder = Decoder()
xbg = XBeeGateway()

decoder.register_callback(decoder.print_dictionary)
xbg.register_callback(decoder.decode_data)


port = raw_input("Please enter your serial port path/name: ")
baud_rate = 9600

xbg.setup_xbee(port, baud_rate)
xbg.begin_test()

