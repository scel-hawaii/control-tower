coordinator-recv
=======================

coordinator-recv is currently a simple device driver and parser which takes in
data from an xbee connected to the server via a ftdi-usb converter, and pushes
the data to a local postgresql database.

The original author is Adam Oberbeck, but heavy modifications have been made by 
me (Kenny Luong) in order to streamline development and create increased 
compatibility. The current coordinator server is in a VERY young state, and has 
many issues.


Requirements:
-----------------------
1. Postgresql
2. A database with the current user's name
3. Postgres configured to accept local connections
4. Python and related modules
    1. psycopg2
    2. python-Xbee
    3. serial
    4. argparse


Internal Description
------------------------

Plain and simple, the `coordinator_server` takes in the raw xbee input, translates it and
stuffs it into a database. Here is a simple sequence of what happens:

1. The data arrives in the XBee's buffer
2. We fetch the raw data using the [Python Xbee Library](http://code.google.com/p/python-xbee/)
    * This is just a wrapper for the [Xbee API mode](http://www.digi.com/support/kbase/kbaseresultdetl?id=2184)
2. The raw data is then unpacked using python's [struct module](https://docs.python.org/2/library/struct.html).
    1. The data is unpacked according to the current packet schema.
    2. The unpacked data is then separated into time separated chunks
        * Each sensor samples at a different period (depending on it's importance)
        * This value is hardcoded into the server
3. An appropriate SQL call is generated to insert each data element
4. An SQL `BEGIN` sequence starts
5. Each element is inserted
    1. If an exception is detected, a `ROLLBACK` is initialized and the output dumped into a debug database

Here is an example of a current packet schema:

    typedef struct {
        uint16_t schema;
        uint16_t address;               // Address of Arduino   
        uint32_t uptime_ms;             // Time since start of program
        uint8_t n;                      // number of data points in packet 0..30
        uint16_t batt_mv[6];            // Battery Voltage (in milli volts)
        uint16_t panel_mv[6];           // Panel Voltage (in milli volts)
        uint32_t bmp085_press_pa;       // Pressure Value (in pascals)
        int16_t bmp085_temp_decic;      // Temperature Value (in celsius)
        uint16_t humidity_centi_pct;
        uint16_t apogee_w_m2[20];
    } schema_3;


Current Issues:
------------------------
* Crappy name
* Not a proper module...
* Poor error handling 
* Poor documentation (always!)



