#!/usr/bin/python
from multiprocessing import Process
from subprocess import call
import time
import serial
import struct
import sys
import os
import datetime

# Run the emu background
def run_base_model():
    cmd = "pwd"
    call([cmd])

    cmd = "./run_emu.sh"
    call([cmd])

def upload(build_dir):
    cmd = "cd " + build_dir + " && avrdude -p m328p -c arduino -P /tmp/simavr-uart0 -U flash:w:firmware.hex"
    print "Running upload command"
    print cmd
    call([cmd], shell=True)

if len(sys.argv) < 2:
    sys.exit("Error, not build specified")

firmware_build = sys.argv[1]
build_dir = "../.pioenvs/" + firmware_build

if os.path.isdir(build_dir) == False:
    sys.exit("Error, firmware build does not exist: " + firmware_build)

if os.path.isfile(build_dir + "/firmware.hex") == False:
    sys.exit("Error, firmware file does not exist. Maybe try compiling? " + firmware_build)

print "Running emulator with build: " + firmware_build

bm_proc= Process(target=run_base_model)
bm_proc.start()

time.sleep(2)

upload_proc = Process(target=upload, args=(build_dir,))
upload_proc.start()

upload_proc.join()

ser = serial.Serial('/tmp/simavr-uart0', 9600)

while True:
    result = ser.read()
    sys.stdout.write(result)
