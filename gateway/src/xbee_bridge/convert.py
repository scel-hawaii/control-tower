import sys
import struct
from xbee.python2to3 import byteToInt, intToByte
from xbee import ZigBee
from xbee.frame import APIFrame

# TODO: write tests;  there are two example TX and cooresponding RX packets

"""
TX: 7e 00 18 10 01 00 00 00 00 00 00 00 00 ff fe 00 00 00 00 ff ff 2c 8d 02 00 2b 02 0b
RX: 7e 00 16 90 00 00 00 00 00 00 00 00 00 00 00 00 00 ff ff 2c 8d 02 00 2b 02 89
"""

# Converts a TX request to a RX frame
def convert_tx_to_rx(raw_frame):
    # TODO: Reject non-tx frames
    length = (ord(raw_frame[1]) << 8)  + ord(raw_frame[2])

    # Extract data from the TX frame
    frame = APIFrame(escaped=True)
    for b in raw_frame:
        frame.fill(b)
    frame.parse()

    parser = XBeeParser()
    sample_data = frame.data
    d = parser._split_response(sample_data)
    tx_data = d['data']

    # Construct the TX frame
    test_frame = APIFrame(escaped=True)
    data_header = "\x90\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    data_body = tx_data
    data = data_header + test_frame.escape(data_body)

    test_frame.data = data
    test_frame.escape(data)
    return test_frame.output()

class XBeeParser():
    def __init__(self):
       self.api_commands = {
       }

       self.api_responses = {
        b'\x90': {
            'name': 'rx',
            'structure': [
                {'name': 'source_addr_long',  'len': 8},
                {'name': 'source_addr',       'len': 2},
                {'name': 'options',           'len': 1},
                {'name': 'rf_data',           'len': None}
            ]
        },

        b'\x10': {
            'name': 'tx',
            'structure': [
                {'name': 'dest_addr_long',   'len': 8},
                {'name': 'dest_addr',        'len': 2},
                {'name': 'broadcast_radius', 'len': 1},
                {'name': 'options',          'len': 1},
                {'name': 'data',             'len': None}
            ]
        },
    }

    def _split_response(self, data):
        """
        _split_response: binary data -> {'id':str,
                                         'param':binary data,
                                         ...}
        _split_response takes a data packet received from an XBee device
        and converts it into a dictionary. This dictionary provides
        names for each segment of binary data as specified in the
        api_responses spec.
        """
        # Fetch the first byte, identify the packet
        # If the spec doesn't exist, raise exception
        packet_id = data[0:1]
        try:
            packet = self.api_responses[packet_id]
        except AttributeError:
            raise NotImplementedError("API response specifications could not "
                                      "be found; use a derived class which "
                                      "defines 'api_responses'.")
        except KeyError:
            # Check to see if this ID can be found among transmittable packets
            for cmd_name, cmd in list(self.api_commands.items()):
                if cmd[0]['default'] == data[0:1]:
                    raise CommandFrameException("Incoming frame with id {} "
                                                "looks like a command frame of "
                                                "type '{}' (these should not be"
                                                " received). Are you sure your "
                                                "devices are in "
                                                "API mode?".format(
                                                    data[0], cmd_name)
                                                )

            raise KeyError(
                "Unrecognized response packet with id byte {0}".format(data[0]))

        # Current byte index in the data stream
        index = 1

        # Result info
        info = {'id': packet['name']}
        packet_spec = packet['structure']

        # Parse the packet in the order specified
        for field in packet_spec:
            if field['len'] == 'null_terminated':
                field_data = b''

                while data[index:index+1] != b'\x00':
                    field_data += data[index:index+1]
                    index += 1

                index += 1
                info[field['name']] = field_data
            elif field['len'] is not None:
                # Store the number of bytes specified

                # Are we trying to read beyond the last data element?
                expected_len = index + field['len']
                if expected_len > len(data):
                    raise ValueError("Response packet was shorter than "
                                     "expected; expected: {}, got: {} "
                                     "bytes".format(expected_len, len(data))
                                     )

                field_data = data[index:index + field['len']]
                info[field['name']] = field_data

                index += field['len']
            # If the data field has no length specified, store any
            #  leftover bytes and quit
            else:
                field_data = data[index:]

                # Were there any remaining bytes?
                if field_data:
                    # If so, store them
                    info[field['name']] = field_data
                    index += len(field_data)
                break

        # If there are more bytes than expected, raise an exception
        if index < len(data):
            raise ValueError("Response packet was longer than expected; "
                             "expected: {}, got: {} bytes".format(
                                 index, len(data))
                             )

        # Apply parsing rules if any exist
        if 'parsing' in packet:
            for parse_rule in packet['parsing']:
                # Only apply a rule if it is relevant (raw data is available)
                if parse_rule[0] in info:
                    # Apply the parse function to the indicated field and
                    # replace the raw data with the result
                    info[parse_rule[0]] = parse_rule[1](self, info)

        return info
