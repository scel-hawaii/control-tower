#!/usr/bin/env python
#
# integration_test.py
#
# This is a system test that uses a bridge (via the linux socat utility) to
# connect a fake tty device with the real system.
#
# TODO: Complete this script
# TODO: Uart Bridge should probably be called something else
#
# Author(s): Kenny Luong <luong97@hawaii.edu>
# Date Created: 2017-09-26
# Date Modified: 2017-10-03
#

import subprocess
import signal
import sys
import time
import os
from tty_bridge import TTYBridge
from threading import Thread
from fake_xbee import FakeXbee

include_path = os.path.dirname(os.path.realpath(__file__)) + "/../src"
sys.path.insert(0, include_path)
from xbee_gateway import XBeeGateway
from decoder import Decoder

test_packet_proc = None

# Setup this handler so that the script ends gracefully
def signal_handler(signal, frame):
    print('You pressed Ctrl+C!')

signal.signal(signal.SIGINT, signal_handler)

#
# SETUP UART BRIDGE
#
# The UART bridge will open up two connections;
# one on ttyV1 and the other on ttyV2
#
# Here is an example data flow:
#
# |Fake Device| --> ttyV1 --> SOCAT Bridge --> ttyV2 --> |packet tester|
#
#
tty_bridge = TTYBridge()
tty_bridge.start()
print("Waiting for the UART bridge to come up...")
time.sleep(2)

#
# SETUP FAKE DEVICE
#
def start_test_packet():
    fake_xbee = FakeXbee('./ttyV1')
    fake_xbee.connect()
    fake_xbee.start_loop()

test_packet_thread = Thread(target=start_test_packet)
test_packet_thread.start()

#
# SETUP PACKET TESTER
#
# This is the python script that normally runs on the laptop
#
# subprocess.call("cd ../src && python packet_tester.py", shell=True)

def print_data(data, timestamp):
    print(timestamp)
    print(data)

decoder = Decoder()
decoder.register_callback(decoder.print_dictionary)

gateway = XBeeGateway()
gateway.register_callback(decoder.decode_data)
gateway.setup_xbee('./ttyV2', 9600)
gateway.begin_loop()


#
# BLOCK UNTIL CONTROL-C
#
test_packet_thread.join()
tty_bridge.wait()
