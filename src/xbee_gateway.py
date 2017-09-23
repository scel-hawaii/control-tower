#!/usr/bin/env python

from xbee import ZigBee
import serial
import datetime
import logging
import sys
import os
import pickle
import time
import threading

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
    # TODO: Understand this extra logic a little more (kill flag, etc.)
    #   I know it has something to do with checking if a real xbee device has stopped
    #   responding or not.
    def begin_test(self, i, t_flag, kill_flag):
	print 'Starting main Gateway Loop\n'
        while(not kill_flag.is_set()):
            f = self.xbee.wait_read_frame()
	    t_flag.set()
            data = f['rf_data']
            timestamp = datetime.datetime.now()
            for callback in self.callbacks:
                callback(data, timestamp)

    """
        Simple main loop with no extra checking
        Added by luong97@hawaii.edu on 2017-09-27
    """
    def begin_loop(self):
        while(True):
            f = self.xbee.wait_read_frame()
            data = f['rf_data']
            timestamp = datetime.datetime.now()
            for callback in self.callbacks:
                callback(data, timestamp)


