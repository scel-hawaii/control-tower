Usage
--------------

The current version of Control Tower should be fairly easy to use. Open
a terminal, change directories to the current Control Tower install
directory.

    ./launch_server.py

The server should then scan the `hardware_profiles` directory and
prompt you for an input. Select the correct profile and control tower
should attempt to launch everything for you. 

Deployment procedures
-------------------------

Deployment procedures right now are a little complicated. 

1. Plug in the box
3. VNC into the production server
    * 192.168.1.38:1
2. Start the coordinator server (select the production profile)
3. Watch to see if a packet comes in
4. Verify that the database has data
    SELECT * FROM outdoor_env ORDER BY db_time DESC

Future improvements needed:

    * A script to check that our data has arrived
    * A script to check the database is updated accordingly.
    * Inital debug messages lasting 10 minutes after system startup

Raspberry Pi Deployment Instructions
------------

*Materials Needed:*

* A monitor with HDMI 
* HDMI Cable
* Power cable (for monitor)
* Raspberry Pi
* Xbee Explorer Board (or equivilent) 
* USB Micro Cable
* USB Charger
* Keyboard
* Ethernet cable
*


*Procedures*

1. Attach the keyboard, monitor and other peripherals
2. Plug in the raspberry pi 
    * At this point, it should cycle on by itself. 
3. Log into the `reis` user with the password `password`
5. Start the reverse autossh tunnel which will allow us to SSH back into the pi
    * run command: `autossh -f -R 19999:localhost:22 reis1remote`
6. Check that the tunnel is working by logging into the reis1remote host
    * run command: `ssh -p 19999 localhost`
5. OPTIONAL: Log out and then log back into the device via SSH 
4. Verify the port the USB explorer is attached to, and edit the hardware profile accordingly
    * unplug and replug the USB explorer board
    * run `dmesg`
    * check which port the device is on
4. Start the server in the home directory   
    * Use the command: `./launch_server.py`
    * Select hokulani deployment
5. Verify that we can get data
    * Deploy the weatherbox and wait for data


Description
-----------------

This repository is mainly a collection of scripts which serve 
the purpose of becoming the de-facto server software for the reis
weatherbox. Any test-benches and production code should be 
placed and tracked in this repository.

The main purpose of the server software is to collect server 
information from the scel weatherboxes and push that data to a 
database program (currently Postgresql), where it can be accessed 
and used. The overall goal of this project is to make an easy to use,
easily scalable and easily deployable piece of software for the 
scel lab. 

Installation Instructions
-----------------------

1. Clone from the git repository
1. Install server dependencies
    - Run the server setup script
    - ^ This script still needs to be created 
2. Install python dependencies
    - Run the python setup script (needs root)
4. Setup a postgres database
    - Go into the postgres user and then add a new user called REIS
    - Add a new database called REIS 
    - Give the user permission to the database
    - Set the database so that the REIS user has the permissions to access it.
    - Remember to go ahead and change the timezone!
4. Import the SQL dump
    - Run the postgresql setup script
5. Setup the permissions for the avr-isp programmer
6. Add user to the dialout group (for access to serial):
    - Might be this link https://bradsprojects.wordpress.com/tag/avrisp-mkii/
    - But I'm not sure since I lost documentation...


Weather API
-------------

Basic REST API server for accessing weatherbox data. Eventually to be used
for inputting data as well (with proper tokens).

# Endpoints

## battery

### battery/[address]

**Optional Query Parameters**
* Start Date: A UTC string with a start datetime.
* End Date: A UTC string with an end date.

Returns the last 50k samples. Given the start and end date query parameters,
the endpoint will return the last 50k samples with those dates as constraints.

**Example:**

No query: `curl http://localhost:16906/battery/151`

With query: `curl http://localhost:16906/battery/343?start_time=2016-04-14+02%3A36%3A00+UTC&end_time=2016-04-16+04%3A36%3A00+UTC`



