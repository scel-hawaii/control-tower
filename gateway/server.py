#!/usr/bin/env python
 
import sys
import os
import argparse
import serial
import time
 
from lib.xbee_gateway import WeatherboxGateway
from lib.mock_xbee import start_mock_xbee
from lib.packet import PacketDecoder, PacketWriter
 
def verify_serial_port(port_path):
    """Verify if the serial port exists and is accessible"""
    try:
        if not os.path.exists(port_path):
            print(f"Error: Serial port {port_path} does not exist")
            return False
 
        # Try to open the port to verify permissions
        ser = serial.Serial(port_path)
        ser.close()
        return True
    except (serial.SerialException, OSError) as e:
        print(f"Error accessing serial port {port_path}: {str(e)}")
        return False
 
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
    parser.add_argument(
        "--db-uri",
        type=str,
        help="Database URI (default: from environment GATEWAY_DB_URI)",
        default=os.environ.get("GATEWAY_DB_URI", "postgresql://gateway@localhost/weatherbox")
    )
 
    args = parser.parse_args()
 
    # Get and verify serial port
    serial_port = get_serial_port_from_args(args)
    if not args.port == "fake" and not verify_serial_port(serial_port):
        sys.exit(1)
 
    # Set up gateway
    print(f"Using serial port: {serial_port}")
    print(f"Using database URI: {args.db_uri}")
 
    writer = PacketWriter(db_uri=args.db_uri)
    decoder = PacketDecoder()
 
    try:
        xbg = WeatherboxGateway(
            serial_port=serial_port,
            decoder=decoder,
            writer=writer
        )
 
        print("Gateway initialized successfully")
        print("Waiting for XBee packets... (Press Ctrl+C to exit)")
 
        packet_count = 0
        def packet_callback(rf_data, timestamp):
            nonlocal packet_count
            packet_count += 1
            if packet_count % 10 == 0:
                print(f"Processed {packet_count} packets...")
        '''while True:
            if xbg.loop(args.exit_after_n):
                break
            packet_count += 1
            if packet_count % 10 == 0:  # Print status every 10 packets
                print(f"Processed {packet_count} packets...")'''
        xbg.call_after_frame_parsed(packet_callback)
        xbg.loop(args.exit_after_n)
 
    except KeyboardInterrupt:
        print("\nShutting down gateway...")
    except serial.SerialException as e:
        print(f"\nSerial port error: {str(e)}")
    except Exception as e:
        print(f"\nUnexpected error: {str(e)}")
    finally:
        sys.exit(0)
 
def get_serial_port_from_args(flags):
    if not flags.port:
        return automatically_determine_serial_port()
 
    if flags.port == "fake":
        serial_port = "./ttyFake"
        print("Starting mock XBee...")
        start_mock_xbee(serial_port)
        return serial_port
 
    return flags.port
 
def automatically_determine_serial_port():
    serial_by_id_path = "/dev/serial/by-id/"
    production_port = "/dev/serial/by-id/usb-FTDI_FT231X_USB_UART_DN01DBGI-if00-port0"
 
    print("Attempting to automatically detect USB FTDI Device...")
 
    if os.path.exists(production_port):
        print("Production environment detected, using hardcoded production port")
        return production_port
 
    if not os.path.exists(serial_by_id_path):
        print(f"Error: Serial device path {serial_by_id_path} does not exist")
        sys.exit(1)
 
    try:
        serial_ports = os.listdir(serial_by_id_path)
    except OSError as e:
        print(f"Error accessing {serial_by_id_path}: {str(e)}")
        sys.exit(1)
 
    if not serial_ports:
        print("Error: No connected serial ports found")
        sys.exit(1)
 
    if len(serial_ports) > 1:
        print("Error: Multiple serial ports detected. Please specify which port to use:")
        for serial_port in serial_ports:
            print(f"  - {os.path.join(serial_by_id_path, serial_port)}")
        sys.exit(1)
 
    selected_port = os.path.join(serial_by_id_path, serial_ports[0])
    print(f"Found serial port: {selected_port}")
    return selected_port
 
if __name__ == "__main__":
    main()
