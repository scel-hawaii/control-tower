#!/usr/bin/env python

import pika
import time

class RMQ:

    def __init__(self):
        port = 8082
        host = 'localhost'

        connection = pika.BlockingConnection(pika.ConnectionParameters(
                           host, port))

        self.channel = connection.channel()
        self.channel.queue_declare(queue='hello')

    def publish(self, data):
        self.channel.basic_publish(exchange='',
                              routing_key='hello',
                              body=d)


queue = RMQ()

while True:
    d = "hello, world"
    queue.publish(d);

    seconds = 0.5
    time.sleep(seconds)

    print "Finished publishing data"


