import pika
import time
import datetime
import json

def callback(ch, method, properties, body):
    packet = json.loads(body)

    s = packet['timestamp'] + " " + packet['data']
    print(s)

connection = pika.BlockingConnection(pika.ConnectionParameters(
            'localhost', 8082))
channel = connection.channel()
channel.queue_declare(queue='hello')

channel.basic_consume(callback,
                      queue='hello',
                      no_ack=True)
while True:
    channel.start_consuming()

