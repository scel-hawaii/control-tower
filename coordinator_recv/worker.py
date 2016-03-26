#!/usr/bin/env python
import pika
import pickle

connection = pika.BlockingConnection(pika.ConnectionParameters(
        host='localhost'))
channel = connection.channel()

channel.queue_declare(queue='hello')

def callback(ch, method, properties, body):
    d = pickle.loads(body)
    print d['timestamp'], d['xbee_frame']['rf_data']

channel.basic_consume(callback,
                      queue='hello',
                      no_ack=True)

while True:
    channel.start_consuming()
