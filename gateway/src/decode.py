from . import decoder
import datetime
import os
import sys
import json


def print_packet(data):
    print((json.dumps(data)))
    sys.stdout.flush()
    # print(data['rf_data'])


if sys.stdin.isatty():
    rf_data = sys.argv[1]
    d = decoder.Decoder()
    d.register_callback(print_packet)
    d.decode_data(rf_data.strip().decode('hex'), datetime.datetime.now())

else:
    # for line in sys.stdin:
    for line in iter(sys.stdin.readline, ''):
        d = decoder.Decoder()
        d.register_callback(print_packet)
        json_decode_error = False
    
        try:
            data_frame = json.loads(line)
        except:
            json_decode_error = True
            print("There was an error trying to decode the json: " + str(line))
    
        if json_decode_error == False:
            d.decode_data(data_frame['rf_data'].strip().decode('hex'), datetime.datetime.now())

