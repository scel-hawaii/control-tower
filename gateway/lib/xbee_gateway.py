#!/usr/bin/env python
import datetime
import logging
import sys
from typing import Callable

import serial
from xbee import ZigBee
from lib.packet import PacketDecoder, PacketWriter



class WeatherboxGateway:
    def __init__(
        self, 
        serial_port: str,
        decoder: PacketDecoder,
        writer: PacketWriter,
        baud_rate: int = 9600,

    ):
        self.callbacks = []
        try:
            ser = serial.Serial(serial_port, baud_rate)
            self.xbee = ZigBee(ser, escaped=True)
        except serial.SerialException as e:
            logging.warning("Serial error")
            logging.warning(str(e))
            sys.exit(1)

        self.decoder = decoder
        self.writer = writer

    def call_after_frame_parsed(self, callback: Callable):
        """
        Register a callback to be executed when data is read from
        the XBee.
        """
        self.callbacks.append(callback)

    def loop(self, return_after_n: int = 0) -> bool:
        """
        Main loop

        Returns True if execution is complete to signal to the top level
        program to exit.
        """
        n = 0
        while True:
            f = self.xbee.wait_read_frame()
            rf_data = f["rf_data"]
            timestamp = datetime.datetime.now()

            schema, packet = self.decoder.decode_packet(rf_data, timestamp)
            self.writer.write_to_filesystem(schema, packet)
            self.writer.write_to_db(schema, packet)
            self.writer.print_dictionary(schema, packet)

            for callback in self.callbacks:
                callback(rf_data, timestamp)

            # Exit after N iterations, useful for testing
            n += 1
            if return_after_n and n > return_after_n:
                return True
