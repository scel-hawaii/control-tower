from xbee import ZigBee
import serial
import datetime
import logging
import sys
import os
import pickle
import time

from xbee_gateway import XBeeGateway

def print_data(d):
    print "Got data"
    data = pickle.loads(d)
    print data['timestamp']

serial_port = "/dev/cu.usbserial-DN01DS4M"
baud_rate = 9600

xbg = XBeeGateway()
xbg.register_callback(print_data)

xbg.setup_xbee(serial_port, baud_rate)
xbg.begin()
