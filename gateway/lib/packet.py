import struct
import collections
import os
import datetime
from typing import Callable
from enum import IntEnum


import psycopg2


# Conversion factors for apogee sensors
# http://www.apogeeinstruments.com/content/SP-100-200-spec-sheet.pdf
SP215_CONVERSION = 0.25  # W/m^2 per mV
SP212_CONVERSION = 0.5  # W/m^2 per mV


class PacketType(IntEnum):
    HEARTBEAT = 0
    APPLE = 1


PACKET_UNPACK_FORMATS = {
    PacketType.HEARTBEAT: "HHIH",
    PacketType.APPLE: "HHIHHIhHH",
}


PACKET_EXPECTED_LENGTHS = {
    PacketType.HEARTBEAT: 10,
    PacketType.APPLE: 22,
}


class PacketDecoder:
    def __init__(self):
        self.callbacks = []

    def call_after_decode(self, callback: Callable):
        self.callbacks.append(callback)

    def decode(self, rf_data: bytes, timestamp: datetime.datetime):
        schema, packet = self.decode_packet(rf_data, timestamp)
        for callback in self.callbacks:
            callback(schema, packet)

    def validate_packet(self, rf_data: bytes) -> bool:
        """
        Checks if the packet has a valid schema
        Returns a boolean and creates schema number variable
        """
        schema_num = struct.unpack("<" + "H", rf_data[0:2])[0]
        print(str(schema_num) + ":" + str(len(rf_data)))

        if not PACKET_UNPACK_FORMATS.get(schema_num):
            print(f"Schema {schema_num} does not exist.")
            return False

        # Verify expected packet lengths in bytes
        if len(rf_data) != PACKET_EXPECTED_LENGTHS[schema_num]:
            return False

        return True

    def decode_packet(self, rf_data: bytes, timestamp: datetime.datetime) -> tuple[int, dict]:
        if not self.validate_packet(rf_data):
            print("Not A Valid Packet\n")
            return -1, {}

        schema = struct.unpack("<" + "H", rf_data[0:2])[0]
        fmt = "<" + PACKET_UNPACK_FORMATS[schema]
        unpacked_data = struct.unpack(fmt, rf_data)

        packet = {}
        packet["time_received"] = str(timestamp)
        if schema == PacketType.HEARTBEAT:
            packet["schema"] = unpacked_data[0]
            packet["node_addr"] = unpacked_data[1]
            packet["uptime_ms"] = unpacked_data[2]
            packet["batt_mv"] = unpacked_data[3]

        elif schema == PacketType.APPLE:
            packet["schema"] = unpacked_data[0]
            packet["node_addr"] = unpacked_data[1]
            packet["uptime_ms"] = unpacked_data[2]
            packet["batt_mv"] = unpacked_data[3]
            packet["panel_mv"] = unpacked_data[4]
            packet["press_pa"] = unpacked_data[5]
            packet["temp_c"] = unpacked_data[6]
            packet["humidity_centi_pct"] = unpacked_data[7]

            # apple box uses apogee sp215
            # https://wiki.scel-hawaii.org/doku.php?id=weather:apple:datasheets
            packet["apogee_w_m2"] = unpacked_data[8] * SP215_CONVERSION

        return schema, collections.OrderedDict(sorted(packet.items()))


class PacketWriter:
    def __init__(self, db_uri: str, filesystem_path: str | None = "./"):
        # A path on the filesystem to write CSV files to
        self.filesystem_path = filesystem_path

        # A URI string to connect to a db
        self.db_uri = db_uri

    def write_to_filesystem(self, schema: int, packet: dict):
        """
        Write the decoded data to respective csv file
        """

        file_name = ""

        node_addr = packet["node_addr"]
        if schema == PacketType.HEARTBEAT:
            file_name = f"heartbeat-{node_addr}.csv"
        elif schema == PacketType.APPLE:
            file_name = f"node-{node_addr}.csv"

        data_string = ""
        for key, value in packet.items():
            data_string += str(value)
            data_string += ","

        data_string = data_string[:-1]
        data_string += "\n"

        file_exists = os.path.isfile(file_name)

        with open(file_name, "a", encoding="utf-8") as csvfile:
            if not file_exists:
                header_string = ""
                for key, value in packet.items():
                    header_string += str(key) + ","
                header_string = header_string[:-1]
                header_string += "\n"
                csvfile.write(header_string)
            csvfile.write(data_string)

    def write_to_db(self, schema: int, packet: dict):
        """
        Write decoded data to respective table in database.

        Skips writing to an external DB if writer is not configured
        with a URI to write to.
        """
        if not self.db_uri:
            return

        # make connection to database, this can be added elsewhere so it will only be done once
        con = psycopg2.connect(self.db_uri)
        cur = con.cursor()

        if schema == PacketType.HEARTBEAT:
            table_name = "heartbeat"
        elif schema == PacketType.APPLE:
            table_name = "apple"
        else:
            print("Invalid packet schema")
            return

        # create a new empty row
        cur.execute(
            "INSERT INTO %s (time_received) VALUES ('%s')"
            % (table_name, packet["time_received"])
        )

        # insert data into newly created row
        for key, value in packet.items():
            if key != "time_received":
                sql_command = "UPDATE %s SET %s = %s WHERE time_received = '%s'" % (
                    table_name,
                    key,
                    str(value),
                    packet["time_received"],
                )
                cur.execute(sql_command)

        con.commit()
        con.close()

    def print_dictionary(self, _, packet: dict):
        for key, value in packet.items():
            print(key + ": " + str(value))
        print("\n")
