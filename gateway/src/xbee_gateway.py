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
import sys
import copy
import uuid
import json
import zmq


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
        while(1):
            f = self.xbee.wait_read_frame()
	    t_flag.set()
            print(f)
            data = f['rf_data']
            timestamp = datetime.datetime.now()
            for callback in self.callbacks:
                callback(data, timestamp)

    """
        Simple main loop with no extra checking
        Added by luong97@hawaii.edu on 2017-09-27
    """
    def begin_loop(self):
        # socket.bind("tcp://*:%s" % port)
        # port = "5556"
        context = zmq.Context()
        socket = context.socket(zmq.PUB)
        socket.bind("ipc://tmp.socket")

        topic = "testing"

        while(True):
            f = self.xbee.wait_read_frame()
            """
            now = datetime.datetime.now()
            sys.stdout.write(str(now))
            sys.stdout.write("  ")
            sys.stdout.write(str(f))
            sys.stdout.write("\n")
            sys.stdout.flush()
            """

            uid = uuid.uuid4()

            f_alt = copy.copy(f)
            f_alt['source_addr_long'] = f_alt['source_addr_long'].encode('hex')
            f_alt['source_addr'] = f_alt['source_addr'].encode('hex')
            f_alt['rf_data'] = f_alt['rf_data'].encode('hex')
            f_alt['options'] = f_alt['options'].encode('hex')
            f_alt['packet_uuid'] = str(uid)
            f_alt['time_recieved'] = str(datetime.datetime.now())

            now = datetime.datetime.now()
            sys.stdout.write(str(now))
            sys.stdout.write("  ")
            sys.stdout.write(json.dumps(f_alt))
            sys.stdout.write("\n")
            sys.stdout.flush()

            # sys.stdout.write(str(f['source_addr_long']).encode('hex'))
            # sys.stdout.write("\n")
            # sys.stdout.flush()

            data = f['rf_data']
            timestamp = datetime.datetime.now()
            socket.send(json.dumps(f_alt))
            socket.send("COOL")
            for callback in self.callbacks:
                callback(data, timestamp)


if __name__ == "__main__":
    xbee_gateway = XBeeGateway()
    # serial_port = "/dev/serial/by-id/usb-FTDI_FT231X_USB_UART_DN00OK9M-if00-port0"
    serial_port = "../test/ttyV2"
    baud_rate = 9600

    xbee_gateway.setup_xbee(serial_port, baud_rate)
    xbee_gateway.begin_loop()

