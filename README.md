control-tower
=======================

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

