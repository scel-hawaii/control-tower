#!/usr/bin/env python
import pika
import cPickle as pickle
import logging
import datetime
import pprint
from decode import PacketDecoder

pp = pprint.PrettyPrinter(indent=4)


decoder = PacketDecoder()
i = 0;

logging.basicConfig(filename='worker.log',level=logging.DEBUG)

connection = pika.BlockingConnection(pika.ConnectionParameters(
        host='localhost'))
channel = connection.channel()
channel.queue_declare(queue='hello')

def parse_data(body):
    timestamp = datetime.datetime.now()
    d = pickle.loads(body)
    rf_data = d['xbee_frame']['rf_data']
    print str(timestamp) + ": --------- Start new packet ----------"
    print decoder.unpack(rf_data)
    print "Finished decoding data"
    print str(timestamp) + ": --------- End new packet ------------"

def callback(ch, method, properties, body):
    parse_data(body)

def consume(channel):
    channel.basic_consume(callback,
                          queue='hello',
                          no_ack=True)
    while True:
        channel.start_consuming()

consume(channel)
