#!/usr/bin/env python

# Simple example of XML-RPC server to expose DB queries. Access the
# functions by, e.g.:
# >>> import xmlrpclib
# >>> p = xmlrpclib.ServerProxy("http://localhost:14158")
# >>> p.last_reading_by_node()
# >>> p.a_hash()

import datetime
from SimpleXMLRPCServer import SimpleXMLRPCServer
import psycopg2

xml_address = ("", 14158)

db_host = "localhost"
db_port = "5432"
db_user = "reis"
db_database = "reis"

def last_reading_by_node():
    c = db_conn.cursor()
    # subtlety: cast time to string only for results, not every row:
    # fixme: seq scan
    c.execute("select raaargh.address, db_time::varchar, bmp085_temp_decic, bmp085_press_pa, batt_mv, panel_mv from raaargh, (select address, max(db_time) from raaargh group by address) a where raaargh.address = a.address and raaargh.db_time = a.max;")
    l = [["address", "db_time", "bmp085_temp_decic", "bmp085_press_pa", "batt_mv", "panel_mv"]]
    l.extend(list(c))
    c.close()
    return l

def last_hour_avg_by_node():
    c = db_conn.cursor()
    c.execute("select address, min(db_time)::varchar as min_db_time, max(db_time)::varchar as max_db_time, count(*) as n, avg(bmp085_temp_decic)::double precision as avg_bmp085_temp_decic, avg(bmp085_press_pa)::double precision as avg_press_pa from raaargh where db_time > now() - '1 hour'::interval group by address;")
    l = [["address", "min_db_time", "max_db_time", "n", "avg_bmp085_temp_decic", "avg_pressure_pa", "avg_batt_mv", "avg_panel_mv"]]
    l.extend(list(c))
    c.close()
    print l
    return l

def help():
    return "last_reading_by_node last_hour_avg_by_node a_list a_hash"


if __name__ == "__main__":
    print "Starting..."
    xml_server = SimpleXMLRPCServer(xml_address)
    xml_server.register_function(last_reading_by_node)
    xml_server.register_function(last_hour_avg_by_node)
    xml_server.register_function(help)

    # xml rpc java testing bullshit
    def a_list(): return [1, 2., "three"]
    xml_server.register_function(a_list)
    def a_hash(): return {'1': 1, '2': 2., '3': "three"}
    xml_server.register_function(a_hash)

    db_conn = psycopg2.connect(host=db_host, port=db_port, 
                               user=db_user, database=db_database)
    # print last_reading_by_node()

    try:
        print "Press C-C to stop."
        xml_server.serve_forever()
    finally:
        print "Stopping..."
        xml_server.server_close()
        db_conn.close()
        print "Stopped."
