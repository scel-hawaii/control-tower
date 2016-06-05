#!/usr/bin/env python

import pika
import time

port = 8082
host = 'localhost'

connection = pika.BlockingConnection(pika.ConnectionParameters(
                   host, port))
channel = connection.channel()
channel.queue_declare(queue='hello')

while True:
    d = "hello, world"
    channel.basic_publish(exchange='',
                          routing_key='hello',
                          body=d)
    seconds = 0.5
    time.sleep(seconds);
