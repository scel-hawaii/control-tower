from xbee import ZigBee
import sys
import serial
import datetime
import struct
import collections
import csv
import os.path
import psycopg2

class Decoder:

  def __init__(self):
    self.schemaDict = {
      'ga_legacy': 'HHBI'+'B'+'H'*6+'H'*6+'IhH'+'H'*20,
      '0': 'HHIH', #Heartbeat schema
      '1': 'HHIHHIhHH', #Apple schema
      '2': 'HHIHHHhHH', #Cranberry schema
      '3': 'HHIHHIhHH'  #Dragonfruit Schema
    }
    self.callbacks = []

  """
  Checks if the packet has a valid schema
  Returns a boolean and creates schema number variable
  """
  def check_schema(self, data):
    self.schema_num = struct.unpack('<' + 'H', data[0:2])[0]
    for key in self.schemaDict:
      if str(self.schema_num) == key:
        return True
    return False


  """
  Main Function
  """
  def decode_data(self, data, timestamp):
    if self.check_schema(data):
      dataDict = self.sort_packet(data, timestamp)
      for callback in self.callbacks:
        callback(dataDict)
    else:
      print "Not A Valid Packet"

  """
  Displays given data dictonary
  """
  def print_dictionary(self, dataDict):
    for key, value in dataDict.iteritems():
      print key + ": " + str(value)

  def write_to_file(self, dataDict):
    fileExists = True

    if(os.path.isfile('data.csv') == False):
	fileExists = False
    dataString = ''
    for key, value in dataDict.iteritems():
	dataString += str(value)
	dataString += ','

    dataString = dataString[:-1]
    dataString += '\n'

    with open('data.csv', 'a') as csvfile:
	if(fileExists == False):
		headerString = ""
		for key, value in dataDict.iteritems():
			headerString += str(key) + ','
		headerString = headerString[:-1]
		headerString += '\n'
		csvfile.write(headerString)
	csvfile.write(dataString)

  def write_to_db(self, dataDict):
    #make connection to database, this can be added elsewhere so it will only be done once
    con = psycopg2.connect("dbname='control_tower' user='control_tower'")
    cur = con.cursor()

    if(self.schema_num == 0):
        #create a new empty row
        cur.execute("INSERT INTO heartbeat (time_received) VALUES ('%s')" %(dataDict["time_received"]))

        #insert data into newly created row
        for key, value in dataDict.iteritems():
            if key != 'time_received':
                sqlCommand = "UPDATE heartbeat SET %s = %s WHERE time_received = '%s'" %(key, str(value), dataDict["time_received"])
                cur.execute(sqlCommand)

#    elif self.schema_num == 1:
                #do stuff

#    elif self.schema_num == 2:
                #do stuff
#    elif self.schema_num == 3:
                #do stuff
    con.commit()

  def register_callback(self, callback):
    self.callbacks.append(callback)

  """
  Sorts data into a specific schema dictionary
  """

  def sort_packet(self, data, timestamp):
    fmt = '<' + self.schemaDict[str(self.schema_num)]
    dataDict = {}
    unpacked_data = struct.unpack(fmt,data)

    dataDict["time_received"] = str(timestamp)
    if self.schema_num == 1: #apple schema
      dataDict["schema"] = unpacked_data[0]
      dataDict["node_addr"] = unpacked_data[1]
      dataDict["uptime_ms"] = unpacked_data[2]
      dataDict["batt_mv"] = unpacked_data[3]
      dataDict["panel_mv"] = unpacked_data[4]
      dataDict["press_pa"] = unpacked_data[5]
      dataDict["temp_c"] = unpacked_data[6]
      dataDict["humidity_centi_pct"] = unpacked_data[7]
      dataDict["apogee_w_m2"] = unpacked_data[8]

    elif self.schema_num == 2: #cranberry schema
      dataDict["schema"] = unpacked_data[0]
      dataDict["node_addr"] = unpacked_data[1]
      dataDict["uptime_ms"] = unpacked_data[2]
      dataDict["batt_mv"] = unpacked_data[3]
      dataDict["panel_mv"] = unpacked_data[4]
      dataDict["apogee_w_m2"] = unpacked_data[5]
      dataDict["temp_c"] = unpacked_data[6]
      dataDict["humidity_centi_pct"] = unpacked_data[7]
      dataDict["press_kpa"] = unpacked_data[8]

    elif self.schema_num == 3: #dragonfruit schema
      dataDict["schema"] = unpacked_data[0]
      dataDict["node_addr"] = unpacked_data[1]
      dataDict["uptime_ms"] = unpacked_data[2]
      dataDict["batt_mv"] = unpacked_data[3]
      dataDict["panel_mv"] = unpacked_data[4]
      dataDict["press_pa"] = unpacked_data[5]
      dataDict["temp_c"] = unpacked_data[6]
      dataDict["humidity_centi_pct"] = unpacked_data[7]
      dataDict["apogee_w_m2"] = unpacked_data[8]

    elif self.schema_num == 0: #heartbeat schema
      dataDict["schema"] = unpacked_data[0]
      dataDict["node_addr"] = unpacked_data[1]
      dataDict["uptime_ms"] = unpacked_data[2]
      dataDict["batt_mv"] = unpacked_data[3]

    return collections.OrderedDict(sorted(dataDict.items()))
