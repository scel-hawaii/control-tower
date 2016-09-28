from xbee import ZigBee
import sys
import serial
import datetime
import struct
import collections

class Decoder:

  def __init__(self):
    self.schemaDict = {
      'ga_legacy': 'HHBI'+'B'+'H'*6+'H'*6+'IhH'+'H'*20, 
      '0': 'HHIH', #Heartbeat schema
      '1': 'HHIHHIhHH', #Apple schema
      '2': 'HHIHHHhHH', #Cranberry schema
      '3': 'HHIHHIhHH'  #Dragonfruit Schema 
    }

  def check_schema(self, data):
    self.schema = struct.unpack('<' + 'H', data[0:2])[0]
    for key in self.schemaDict:
      if str(self.schema) == key:
        return True   
    return False

  def decode_data(self, data):
    if self.check_schema(data):
      dataDict = self.sort_packet(data)
      self.print_data(dataDict)
    else:
      print "Not A Valid Packet"

  def print_data(self, dataDict):
    orderedData = collections.OrderedDict(sorted(dataDict.items()))
    for key, value in orderedData.iteritems():
      print key + ": " + str(value) 

  def sort_packet(self, data):
    fmt = '<' + self.schemaDict[str(self.schema)]
    
    dataDict = {}
    unpacked_data = struct.unpack(fmt,data)

    if self.schema == 1: #apple schema
      dataDict["schema"] = unpacked_data[0]
      dataDict["node_addr"] = unpacked_data[1]
      dataDict["uptime_ms"] = unpacked_data[2]
      dataDict["batt_mv"] = unpacked_data[3]
      dataDict["panel_mv"] = unpacked_data[4]
      dataDict["press_pa"] = unpacked_data[5]
      dataDict["temp_c"] = unpacked_data[6]
      dataDict["humidity_centi_pct"] = unpacked_data[7]
      dataDict["apogee_w_m2"] = unpacked_data[8]

    elif self.schema == 2: #cranberry schema
      dataDict["schema"] = unpacked_data[0]
      dataDict["node_addr"] = unpacked_data[1]
      dataDict["uptime_ms"] = unpacked_data[2]
      dataDict["batt_mv"] = unpacked_data[3]
      dataDict["panel_mv"] = unpacked_data[4]
      dataDict["apogee_w_m2"] = unpacked_data[5]
      dataDict["temp_c"] = unpacked_data[6]
      dataDict["humidity_centi_pct"] = unpacked_data[7]
      dataDict["press_kpa"] = unpacked_data[8]
    
    elif self.schema == 3: #dragonfruit schema
      dataDict["schema"] = unpacked_data[0]
      dataDict["node_addr"] = unpacked_data[1]
      dataDict["uptime_ms"] = unpacked_data[2]
      dataDict["batt_mv"] = unpacked_data[3]
      dataDict["panel_mv"] = unpacked_data[4]
      dataDict["press_pa"] = unpacked_data[5] 
      dataDict["temp_c"] = unpacked_data[6]
      dataDict["humidity_centi_pct"] = unpacked_data[7]
      dataDict["apogee_w_m2"] = unpacked_data[8]
      
    elif self.schema == 0: #heartbeat schema
      dataDict["schema"] = unpacked_data[0]
      dataDict["node_addr"] = unpacked_data[1]
      dataDict["uptime_ms"] = unpacked_data[2]
      dataDict["batt_mv"] = unpacked_data[3]

    return dataDict 

  


