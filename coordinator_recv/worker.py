#!/usr/bin/env python
import pika
import pickle
import logging

logging.basicConfig(filename='worker.log',level=logging.DEBUG)

connection = pika.BlockingConnection(pika.ConnectionParameters(
        host='localhost'))
channel = connection.channel()

channel.queue_declare(queue='hello')

def callback(ch, method, properties, body):
    d = pickle.loads(body)

    s = str(d['timestamp']) +  str(d['xbee_frame']['rf_data'])
    logging.info(s)

channel.basic_consume(callback,
                      queue='hello',
                      no_ack=True)

while True:
    channel.start_consuming()
