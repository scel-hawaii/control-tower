#!/usr/bin/env python
import pika
import cPickle as pickle
import logging
import datetime
import pprint
import psycopg2
from decode import PacketDecoder

pp = pprint.PrettyPrinter(indent=4)


conn = psycopg2.connect(host="127.0.0.1", user="kluong", password="hello")
cur = conn.cursor()

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

    store_db(rf_data)

def store_db(rf_data):
    global cur
    try:
        cur.execute('BEGIN;')
        for t in decoder.decode(rf_data):
            cur.execute(decoder.create_query(t), t['values'])
        cur.execute('COMMIT;')
    except Exception, e:
        cur.execute('ROLLBACK;')
        cur.execute('BEGIN;')
        cur.execute(
                '''INSERT INTO outdoor_env_unrecognized (db_time, rf_data, exception) VALUES (now(), %s, %s);''',
                [buffer(rf_data), str(sys.exc_info()[0]) + ': ' + str(e)])
        cur.execute('COMMIT;')

def callback(ch, method, properties, body):
    parse_data(body)

def consume(channel):
    channel.basic_consume(callback,
                          queue='hello',
                          no_ack=True)
    while True:
        channel.start_consuming()


timestamp = datetime.datetime.now()
print str(timestamp) + "Starting worker process."
consume(channel)
