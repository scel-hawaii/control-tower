#
# graph.py
#
# Author:   Kenny Luong <luong97@hawaii.edu>
# Date:     2016-12-01
#
# A simple program that graphs sensor data.
#

import matplotlib
matplotlib.use('Agg')

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import time
import csv
import math
import psycopg2
import psycopg2.extras
import os
import datetime
from multiprocessing import Pool, TimeoutError

def graph_box(generation, node_addr, date, force_redraw=False):
    print "Graphing address %s on date %s" % (node_addr, date)

    # Check if the path exists
    # replace the date for the filename
    date_nosep = date.replace("-", "")

    # If the directory already exists we likely already
    # plotted it, so don't plot it again.
    #
    # if force_redraw is enabled, then bypass this check
    path = "public_html/graphs/%s/%s" % (node_addr, date_nosep)
    if ( os.path.exists(path) and force_redraw == False):
        print "\tGraph directory already exists"
        print "\t" + str(path)
        return True

    # Note: it may be more efficient, if for every address we
    # queue the aggregate per day before.
    #
    # This is how we can do it:
    #
    # SELECT date_trunc('day', db_time) AS day_start,
    #    COUNT(*) AS user_count FROM outdoor_env WHERE address=151
    # GROUP BY date_trunc('day', db_time);

    # Run the database query
    results = []
    conn = psycopg2.connect("dbname='control_tower' user='control_tower' host='localhost' password='password'")
    cur = conn.cursor(cursor_factory = psycopg2.extras.RealDictCursor)

    if( generation == "apple" ):
        query = """
        SELECT * FROM apple
        WHERE node_addr = %s
        AND
        DATE(time_received) = %s
        ORDER BY time_received
        """

    elif(generation == "cranberry"):
        query = """
        SELECT * FROM cranberry
        WHERE node_addr = %s
        AND
        DATE(time_received) = %s
        ORDER BY time_received
        """

    elif(generation == "dragonfruit"):
        query = """
        SELECT * FROM dragonfruit
        WHERE node_addr = %s
        AND
        DATE(time_received) = %s
        ORDER BY time_received
        """

    elif(generation == "old"):
        query = """
        SELECT * FROM outdoor_env
        WHERE address = %s
        AND
        DATE(db_time) = %s
        AND
        uptime_ms IS NOT NULL
        ORDER BY db_time
        """

    else:
        query = """
        SELECT * FROM apple
        WHERE node_addr = %s
        AND
        DATE(time_received) = %s
        ORDER BY time_received
        """

    cur.execute(query, (node_addr, date))
    rows = cur.fetchall()

    for row in rows:
        results.append(row)

    # The path could not exist yet if this is the first time we're rendering
    # the graph
    if ( not os.path.exists(path) ):
        print "\tCreating path %s" % path
        os.makedirs(path)

    if( len(results) <= 0):
        print "\t No data for %s" % date
        conn.close()
        return False


    df = pd.DataFrame(results)

    # Export the data to a csv file to allow users to easily
    # download datasets.
    s = df.to_csv("%s/%s_data.csv" % (path, node_addr), index=False)

    # replace the date for the filename
    date = date.replace("-", "")

    # Graph
    p = df.plot(y="panel_mv")
    fig = p.get_figure()

    filename = "%s/panel_mv.png" % (path)
    fig.savefig(filename)

    p = df.plot(y="batt_mv")
    fig = p.get_figure()

    filename = "%s/batt_mv.png" % (path)
    fig.savefig(filename)

    p = df.plot(y="uptime_ms")
    fig = p.get_figure()

    filename = "%s/uptime_ms.png" % (path)
    fig.savefig(filename)

    if( generation == "apple"):
        p = df.plot(y="apogee_w_m2")
        fig = p.get_figure()
    elif( generation == "old"):
        p = df.plot(y="apogee_w_m2")
        fig = p.get_figure()
    else:
        p = df.plot(y="apogee_sp215")
        fig = p.get_figure()

    filename = "%s/apogee_w_m2.png" % (path)
    fig.savefig(filename)

    # close plots so we don't get warnings about memory
    plt.close("all")

    conn.close()
    return True

def graph_box_true(date):
    redraw = False
    if("FORCE_REDRAW" in os.environ):
        print "Force Redraw Enabled"
        redraw = True

    graph_box("apple", "101", date, redraw)
    graph_box("cranberry", "779", date, redraw)
    graph_box("old", "151", date, redraw)

if __name__ == '__main__':
    pool = Pool(processes=8)              # start 4 worker processes

    # Generate a list of dates
    datelist = pd.date_range(start="01/01/2015", end=pd.datetime.today(), freq="D").tolist()

    dates = []

    for date in datelist:
        ds = date.strftime('%Y-%m-%d')
        dates.append(ds)

    pool.map(graph_box_true, dates)

    today = pd.datetime.today().strftime('%Y-%m-%d')

    # Graph the latest data for today
    graph_box("apple", "101", today, True)
