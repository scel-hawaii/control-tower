#!/usr/bin/env python
import pika
import cPickle as pickle
import logging
import datetime
from decode import PacketDecoder


decoder = PacketDecoder()
i = 0;

logging.basicConfig(filename='worker.log',level=logging.DEBUG)

connection = pika.BlockingConnection(pika.ConnectionParameters(
        host='localhost'))
channel = connection.channel()
channel.queue_declare(queue='hello')

def parse_data(body):
    d = pickle.loads(body)
    rf_data = d['xbee_frame']['rf_data']
    decoder.decode(rf_data)
    print "Finished decoding data"

def callback(ch, method, properties, body):
    # thread.start_new_thread( parse, (body,))
    parse_data(body)

def consume(channel):
    channel.basic_consume(callback,
                          queue='hello',
                          no_ack=True)
    while True:
        channel.start_consuming()

consume(channel)
