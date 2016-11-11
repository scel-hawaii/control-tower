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

    """
        Set up an XBee Device
    """
    def setup_xbee(self, serial_port, baud_rate):
        print "Setup XBee Device"
        try:
            ser = serial.Serial(serial_port, baud_rate)
            self.xbee = ZigBee(ser, escaped=True)
        except serial.serialutil.SerialException as e:
            print "Serial Error: ", e
            logging.warning("Serial error")
            logging.warning(str(e))
            sys.exit(1)

    """
        Register a callback to be executed when data is read from
        the XBee.
    """
    def register_callback(self, callback):
        self.callbacks.append(callback)


    """
        Main loop for the gateway. This is run when you want to start
        the gateway.
    """
    def begin(self):
        while True:
            xbee_frame = self.xbee.wait_read_frame()
            d = self.process_packet(xbee_frame)
            for callback in self.callbacks:
                callback(d)

    """
        Begin a fake loop using a sample RX packet
        defined in 'save.p'. Useful for debugging purposes.
    """
    def begin_fake(self):
        xbee_frame = pickle.load( open( "save.p", "rb" ) )
        while True:
            time.sleep(1)
            d = self.process_packet(xbee_frame)
            for callback in self.callbacks:
                callback(d)

    """
        Timestamp an xbee frame that comes in from an XBee Device
    """
    def process_packet(self, xbee_frame):
        data = {
                "timestamp": datetime.datetime.now(),
                "xbee_frame": xbee_frame
               }
        return pickle.dumps(data)

    def begin_test(self):
        while True:
            f = self.xbee.wait_read_frame()
            data = f['rf_data']          
            timestamp = datetime.datetime.now()            
            for callback in self.callbacks:
                callback(data, timestamp)
        
                  

# Self Test
if __name__ == "__main__":
    def print_data(d):
        print "Got data"
        data = pickle.loads(d)
        print data['timestamp']

    xbg = XBeeGateway()
    xbg.register_callback(print_data)
    # xbg.setup_xbee()
    xbg.begin_fake()
