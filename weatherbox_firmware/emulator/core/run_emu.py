#!/usr/bin/python
from subprocess import call
from subprocess import Popen
import time
import serial
import struct
import sys
import os
import datetime
import signal

#
# Check arguments and files
#

if len(sys.argv) < 2:
    sys.exit("Error, not build specified")

firmware_build = sys.argv[1]
build_dir = "../../.pioenvs/" + firmware_build

if os.path.isdir(build_dir) == False:
    sys.exit("Error, firmware build does not exist: " + firmware_build)

if os.path.isfile(build_dir + "/firmware.hex") == False:
    sys.exit("Error, firmware file does not exist. Maybe try compiling? " + firmware_build)

if( not os.path.exists("emu_output.txt")):
    print("emu_output.txt does not exist")
    call(["touch emu_output.txt"], shell=True)

if( os.path.exists("emu_online.txt")):
    call(["rm emu_online.txt"], shell=True)

#
# Main execution
#

bufsize = 0
output_file = open("emu_output.txt", "a", bufsize)

print("Running emulator with build: " + firmware_build)

launch_emu_cmd = "emu_base_model/obj-*/emu_base_model.elf emu_base_model/*.ihex"
emu_proc = Popen([launch_emu_cmd], shell=True, stdout=output_file, stderr=output_file)

# Block and wait for the emulator model to come online
# otherwise we don't be able to upload
#
# The base emulator model writes to emu_online.txt when
# it is online.
while( not os.path.exists("emu_online.txt") ):
    time.sleep(0.01)

print("Running upload command")

upload_cmd = "cd " + build_dir + " && avrdude -p m328p -c arduino -P /tmp/simavr-uart0 -U flash:w:firmware.hex"
# Use the 'call' command here to block execution until we want to
# start reading from the virtual serial port
upload_proc = call([upload_cmd], shell=True, stdout=output_file, stderr=output_file)

ser = serial.Serial('/tmp/simavr-uart0', 9600)

# Define a term handler here or else the emu_proc won't get
# killed properly when SIGTERM gets called in the server
def signal_term_handler(signal, frame):
    global emu_proc
    emu_proc.terminate()
    # print 'got SIGTERM'
    sys.exit(0)

signal.signal(signal.SIGTERM, signal_term_handler)

while True:
    result = ser.read()
    output_file.write(result)
    # sys.stdout.write(result)
