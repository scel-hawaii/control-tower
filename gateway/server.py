#!/usr/bin/env python

import sys
import os
import argparse

from lib.xbee_gateway import WeatherboxGateway
from lib.mock_xbee import start_mock_xbee
from lib.packet import PacketDecoder, PacketWriter


def main():
    parser = argparse.ArgumentParser(
        prog="server.py",
        description="Parses, decodes and writes weatherbox packets",
    )
    parser.add_argument(
        "--port",
        type=str,
        help="Path to the serial port (/dev/ttyUSB0, etc.). Use 'fake' to use simulated traffic.",
    )
    parser.add_argument(
        "--exit-after-n",
        type=int,
        help="Exit after parsing N amount of packets. Useful for testing with fake mode.",
        default=0,
    )
    args = parser.parse_args()
    serial_port = get_serial_port_from_args(args)

    exit_after_n = args.exit_after_n
    gateway_db_uri = os.environ.get("GATEWAY_DB_URI", "")

    if not gateway_db_uri:
        print("Warning: GATEWAY_DB_URI not set, db writes will be skipped.")

    writer = PacketWriter(db_uri=gateway_db_uri)
    decoder = PacketDecoder()

    xbg = WeatherboxGateway(
        serial_port=serial_port,
        decoder=decoder,
        writer=writer
    )

    while True:
        if xbg.loop(exit_after_n):
            break

def get_serial_port_from_args(flags):
    if not flags.port:
        return automatically_determine_serial_port()

    if flags.port == "fake":
        serial_port = "./ttyFake"
        start_mock_xbee(serial_port)
        return serial_port

    return flags.port


def automatically_determine_serial_port():
    serial_by_id_path = "/dev/serial/by-id/"
    production_port = "/dev/serial/by-id/usb-FTDI_FT231X_USB_UART_DN01DBGI-if00-port0"

    print("Attempting to automatically setting port for USB FTDI Device")

    if os.path.exists(production_port):
        print("Production environment detected, returning hardcoded production port")
        return production_port

    serial_ports = os.listdir(serial_by_id_path)
    if not serial_ports:
        print("Error: there were are no connected serial ports")
        sys.exit(1)

    if len(serial_ports) > 1:
        print(
            "Error: more than one connected serial port, cannot determine the correct port."
        )
        print("You have to manually specify the port... here are your options:")
        for serial_port in serial_ports:
            print((os.path.join(serial_by_id_path, serial_port)))
        sys.exit(1)

    return os.path.join(serial_by_id_path, serial_ports[0])


if __name__ == "__main__":
    main()
