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
        self.serial = None
        self.xbee = None
        self.packet = 0
 
        try:
            # Initialize serial first
            self.serial = serial.Serial(serial_port, baud_rate, timeout=1)
            print(f"Serial port opened on {serial_port} at {baud_rate} baud")
 
            # Then initialize XBee
            self.xbee = ZigBee(self.serial, escaped=True)
            print("XBee interface initialized")
 
        except serial.SerialException as e:
            logging.error("Serial error: %s", str(e))
            self.cleanup()
            sys.exit(1)
        except Exception as e:
            logging.error("Unexpected error during initialization: %s", str(e))
            self.cleanup()
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
        Main loop with improved error handling
        """
        n = 0
        try:
            print("Starting main loop - waiting for XBee data...")
            while True:
                try:
                    if not self.serial or not self.serial.is_open:
                        raise Exception("Serial port not open")
 
                    # Read frame
                    f = self.xbee.wait_read_frame()
 
                    # Verify rf_data exists in frame
                    if 'rf_data' not in f:
                        print("Received frame without rf_data")
                        continue
 
                    rf_data = f["rf_data"]
                    timestamp = datetime.datetime.now()
 
                    print(f"Received frame with {len(rf_data)} bytes")
 
                    # Process the packet
                    schema, packet = self.decoder.decode_packet(rf_data, timestamp)
                    if schema != -1:  # Only process valid packets
                        self.writer.write_to_filesystem(schema, packet)
                        #self.writer.write_to_db(schema, packet)
                        self.writer.print_dictionary(schema, packet)
 
                        for callback in self.callbacks:
                            callback(rf_data, timestamp)
 
                    # Exit after N iterations if specified
                    n += 1
                    if return_after_n and n >= return_after_n:
                        print("Reached specified iteration limit")
                        return True
 
                except Exception as e:
                    print(f"Error in packet processing loop: {str(e)}")
                    if "Serial port not open" in str(e):
                        return False
                    continue
 
        except KeyboardInterrupt:
            print("\nReceived interrupt signal - shutting down...")
            self.cleanup()
            sys.exit(0)  # Exit the program gracefully
 
        except Exception as e:
            print(f"Unexpected error: {str(e)}")
            self.cleanup()
            sys.exit(1)  # Exit with error status
 
        return False
 
    def cleanup(self):
        """Cleanup resources with proper order and error handling"""
        try:
            # First halt XBee if it exists
            if self.xbee is not None:
                try:
                    print("Halting XBee interface...")
                    self.xbee.halt()
                except Exception as e:
                    print(f"Error halting XBee: {str(e)}")
                finally:
                    self.xbee = None
 
            # Then close serial if it exists
            if self.serial is not None:
                try:
                    if self.serial.is_open:
                        print("Closing serial port...")
                        self.serial.close()
                except Exception as e:
                    print(f"Error closing serial port: {str(e)}")
                finally:
                    self.serial = None
 
        except Exception as e:
            print(f"Error during cleanup: {str(e)}")
 
