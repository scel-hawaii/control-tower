#!/usr/bin/env python

from xbee import ZigBee
import serial
import datetime
import logging
import sys
import os
import pickle

class XBeeGateway:

    def initialize(self):
        print "Setup"
        self.callbacks = []

    def register_callback(self, callback):
        self.callbacks.push()

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
            data = {
                    "timestamp": datetime.datetime.now(),
                    "xbee_frame": xbee_frame
                    }
            d = pickle.dumps(data)

            s = "[" + str(datetime.datetime.now()) + "] " + "Published xbee frame"
            logging.info(s)

            for callback in callbacks:
                callback(d)


if __name__ == "__main__":
    xbg = XBeeGateway()
    xbg.setup()
    xbg.begin()
