#!/usr/bin/env python
#
# fake_xbee.py
#
# This is a fake xbee that continiously
# spit out packets
#
# This module will block.
#
import serial
import time
import sys
import datetime

class FakeXbee:
    def __init__(self, serial_port):
        self.serial_port = serial_port
        pass

    # connect to the serial port
    def connect(self):
        try:
            self.ser = serial.Serial(self.serial_port, 9600)
        except serial.serialutil.SerialException as e:
            print("Serial Error: ", e)
            sys.exit(1)

    # starts the loop where this device writes fake data
    def start_loop(self):
        #change strings to bytes then save to packets
        packets = {}
        heartbeat_string = "\x7e\x00\x16\x90\x00\x7d\x33\xa2\x00\x40\xe6\x4b\x5e\x03\xfd\x01\x00\x00\xff\xff\xf0\xfa\x23\x00\x2b\x02\xb2"
        packets['heartbeat'] = heartbeat_string.encode('utf-8')
        apple_string = "\x7e\x00\x22\x90\x00\x7d\x33\xa2\x00\x40\x9f\x27\xa7\x29\x6c\x01\x01\x00\xff\xff\x80\x6f\x69\x3d\x06\x0f\x71\x7d\x33\x5a\x8a\x01\x00\x76\x01\x22\x00\x6e\x09\x55"
        packets['apple'] = apple_string.encode('utf-8')
        cranberry_string = "\x7e\x00\x22\x90\x00\x7d\x33\xa2\x00\x41\x25\xe5\x88\x0c\x83\x01\x02\x00\xff\xff\x7c\xf3\x05\x00\xba\x0f\x5c\x08\x05\x00\x20\x73\x3b\x00\xdd\x8b\x01\x00\x7a"
        packets['cranberry'] = cranberry_string.encode('utf-8')
        dragonfruit_string = "\x7e\x00\x24\x90\x00\x7d\x33\xa2\x00\x40\xe6\x72\x7d\x5e\x30\x18\x01\x03\x00\xff\xff\x30\xc8\x07\x00\x6b\x0d\xf4\x00\x06\x00\x00\x00\xb6\x72\x37\x00\xfe\x8b\x01\x00\x00"
        packets['dragonfruit'] = dragonfruit_string.encode('utf-8')
        snapdragon_string = "\x7e\x00\x22\x90\x00\x7d\x33\xa2\x00\x40\xa3\x53\x7d\x5e\x20\x9c\x01\x04\x00\xff\xff\x12\xe4\x49\x00\xca\x0d\x44\x0c\x2c\x31\x01\x00\x2f\x01\x34\x00\x64\x00\xbb"
        packets['snapdragon'] = snapdragon_string.encode('utf-8')
        badPacket_string = "\x7e\x00\x16\x90\x00\x7d\x33\xa2\x00\x40\xe6\x4b\x5e\x03\xfd\x01\x00\x59\x90\x95\x95\x94\x88\x48\x48\x49\xe2"
        packets['badPacket'] = badPacket_string.encode('utf-8')

        while(True):
            for key in packets:
                self.ser.write(packets[key])
                sys.stdout.write( str(datetime.datetime.now()) )
                sys.stdout.write( "  " )
                sys.stdout.write( "Wrote packet to serial - packet type: %s \n" % key )
                sys.stdout.flush()
                time.sleep(0.50)

if __name__ == '__main__':
    xbee = FakeXbee('./ttyV1')
    xbee.connect()
    xbee.start_loop()

