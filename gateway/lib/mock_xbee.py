"""
Mock an xbee - prints out fake traffic in a loop in the background
"""

import os
import time
import serial
from xbee import ZigBee

from lib.mock_serial import MockSerialPTY
from lib.xbee_utils import serialize_frame


def valid_packets():
    packets = {}
    packets["heartbeat"] = (
        b"\x7e\x00\x16\x90\x00\x7d\x33\xa2\x00\x40\xe6\x4b\x5e\x03\xfd\x01\x00\x00\xff\xff\xf0\xfa\x23\x00\x2b\x02\xb2"
    )
    packets["apple"] = (
        b"\x7e\x00\x22\x90\x00\x7d\x33\xa2\x00\x40\x9f\x27\xa7\x29\x6c\x01\x01\x00\xff\xff\x80\x6f\x69\x3d\x06\x0f\x71\x7d\x33\x5a\x8a\x01\x00\x76\x01\x22\x00\x6e\x09\x55"
    )
    return packets


def write_loop(master_fd):
    packets = valid_packets()
    while True:
        for _, packet in packets.items():
            os.write(master_fd, packet)
            time.sleep(0.5)


def read_loop(fd):
    ser = serial.Serial(os.ttyname(fd), 9600)
    xbee = ZigBee(ser, escaped=True)

    while True:
        f = xbee.wait_read_frame()
        f = serialize_frame(f)
        print(f"mock_xbee read frame: {f}")


def start_mock_xbee(pty_path):
    mock_serial = MockSerialPTY(pty_path, write_loop=write_loop, read_loop=read_loop)
    mock_serial.start()
