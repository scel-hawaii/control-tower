#!/usr/bin/env python

# A quick script to grab data from a queue on rabbitmq, parse it and
# then display it.

import pika
import time
import datetime
import json
import logging

def callback(ch, method, properties, body):
    packet = json.loads(body)

    s = packet['timestamp'] + " " + packet['data']
    print(s)
    logging.info(s)

logging.basicConfig(filename='worker_fake.log',level=logging.DEBUG)
connection = pika.BlockingConnection(pika.ConnectionParameters(
            'localhost', 8082))
channel = connection.channel()
channel.queue_declare(queue='hello')

channel.basic_consume(callback,
                      queue='hello',
                      no_ack=True)
while True:
    channel.start_consuming()

