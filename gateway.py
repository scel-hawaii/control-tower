#!/usr/bin/env python

from xbee import ZigBee
import serial
import datetime
import logging
import sys
import os
import pickle
import time

class XBeeGateway:

    def __init__(self):
        print "Setup"
        self.callbacks = []

    def register_callback(self, callback):
        self.callbacks.append(callback)

    def setup(self):
        print "Init XBeeGateway"
        ser_port = '/dev/ttyUSB0'
        baud_rate = 9600
        try:
            ser = serial.Serial(ser_port, baud_rate)
            xbee = ZigBee(ser, escaped=True)
        except serial.serialutil.SerialException as e:
            print "Serial Error: ", e
            logging.warning("Serial error")
            logging.warning(str(e))
            sys.exit(1)


    def begin(self):
        while True:
            xbee_frame = xbee.wait_read_frame()
            d = self.process_packet(xbee_frame)
            for callback in self.callbacks:
                callback(d)

    def begin_fake(self):
        xbee_frame = pickle.load( open( "save.p", "rb" ) )
        while True:
            time.sleep(1)
            d = self.process_packet(xbee_frame)
            for callback in self.callbacks:
                callback(d)

    def process_packet(self, xbee_frame):
        data = {
                "timestamp": datetime.datetime.now(),
                "xbee_frame": xbee_frame
               }
        return pickle.dumps(data)

if __name__ == "__main__":
    def print_data(d):
        print "Got data"
        data = pickle.loads(d)
        print data['timestamp']

    xbg = XBeeGateway()
    xbg.register_callback(print_data)
    # xbg.setup()
    xbg.begin_fake()
