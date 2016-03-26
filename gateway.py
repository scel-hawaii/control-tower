#!/usr/bin/env python

from xbee import ZigBee
import serial
import datetime
import pika
import pickle

connection = pika.BlockingConnection(pika.ConnectionParameters(
                   'localhost'))
channel = connection.channel()
channel.queue_declare(queue='hello')

try:
    ser_port = '/dev/ttyUSB0'
    baud_rate = 9600
    ser = serial.Serial(ser_port, baud_rate)
    xbee = ZigBee(ser, escaped=True)
except serial.serialutil.SerialException as e:
    print "Serial Error: ", e
    sys.exit(1)

while True:
    xbee_frame = xbee.wait_read_frame()
    data = {
            "timestamp": datetime.datetime.now(),
            "xbee_frame": xbee_frame
            }
    d = pickle.dumps(data)

    channel.basic_publish(exchange='',
                          routing_key='hello',
                          body=d)
    print "[" + str(datetime.datetime.now()) + "] " + "Published xbee frame"
