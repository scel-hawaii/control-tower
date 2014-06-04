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

