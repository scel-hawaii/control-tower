coordinator-recv
=======================

coordinator-recv is currently a simple device driver and parser which takes in
data from an xbee connected to the server via a ftdi-usb converter, and pushes
the data to a local Postgresql database.


The original author is Adam Oberbeck, but heavy modifications have been made by 
me (Kenny Luong) in order to streamline development and create increased 
compatibility. The current coordinator server is in a VERY young state, and has 
many issues. 

Current issues:
    * Need to abstract the device driver out from the parser 
    * Broken error detection, crashes will crash the device regardless.
    * Unstreamlined code - self explanatory.

        

