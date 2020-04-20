# Converts TX requests sent through uart on one side to RX
# frames on the other side

from xbee import ZigBee
import sys
import serial
import convert
import errno
import atexit
import os
import threading

def symlink_force(target, link_name):
    try:
        os.symlink(target, link_name)
    except OSError, e:
        if e.errno == errno.EEXIST:
            os.remove(link_name)
            os.symlink(target, link_name)
        else:
            raise e

class XBeeBridge:
    def __init__(self,
            input_port,
            output_port,
            verbose=False
        ):
        self.output_port = output_port
        self.input_port = input_port
        pass

    def read_xbee_frame(self, xbee, master_fd):
        # Convert the escaped frame into a raw unescaped frame
        raw_frame = xbee._wait_for_frame()
        raw_frame.parse()

        # TODO: Create a new APIFrame object and fill that instead of this hack
        raw_frame.raw_data = ""
        raw_output = raw_frame.output()

        sys.stdout.write("TX: ")
        for b in raw_output:
            sys.stdout.write("{0:0{1}x}".format(int(b.encode('hex'), 16),2))
            sys.stdout.write(" ")
        print ""

        # Do the conversion here
        rx_frame = convert.convert_tx_to_rx(raw_output)

        sys.stdout.write("RX: ")
        for b in rx_frame:
            sys.stdout.write("{0:0{1}x}".format(int(b.encode('hex'), 16),2))
            sys.stdout.write(" ")
        print ""
        print ""

        os.write(master_fd, rx_frame)

        return raw_output

    def run_background(self):
        x = threading.Thread(target=self.run, args=())
        x.daemon = True

        x.start()

    def run(self):
        baud_rate = 9600

        master_fd, slave_fd = os.openpty()
        symlink_force(os.ttyname(slave_fd), self.output_port)

        ser = serial.Serial(self.input_port, baud_rate)
        xbee = ZigBee(ser, escaped=True)

        while True:
            self.read_xbee_frame(xbee, master_fd)
