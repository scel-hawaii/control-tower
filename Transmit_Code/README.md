# Transmit Code Test Directory

Used to test the XBEE and transfer functions for each generation.  This contains the basic funtions and operations of the Transmit Module.  This ONLY tests transmitting hard-coded packets on each board to an XBEE connected to XCTU.

All test directories contain the Configuration Module.

Note: This test module requires the XBEEs to be configured properly and on the same network (same pan ID).  Configuration of XBEEs are done through XCTU.

# Tools

1. XCTU
2. Arduino IDE
3. Programmer
4. 2 XBEEs

# Obtaining Transmit Module

1. Pull/Download zip of Transmit_Code and the library directory, libraries
2. Put the libraries directory in the Arduino folder
   * Add contents to the libraries directory if a libraries directory already exists here.
   * This directory was made when installing and setting up the Arduino IDE.
3. Open the .ino file.
4. Navigate to the tab named config.h in Arduino IDE.
5. Comment out any other declared generation and uncomment the generation to be ran on.
6. Uncomment the method of transmission you wish to test and comment out the other method (UART v.s. Binary).

# Set-Up Arduino IDE

1. Under Tools check:
   * Board is set correct (usually Arduino UNO).
   * Port is set correctly (the USB with the programmer plugged into it).
   * Programmer is set correctly (usually AVRISP mkII).
2. Do a test compile to ensure the libraries are found correctly and no other errors exist.
3. Plug programmer into board.

# Testing (using Arduino board)
Apple:

1. Click the upload button (arrow pointing to the right, next to the compile button).
2. Once uploading is complete, the board will now be sending a packet of hard coded information.
3. The XBEE attached to XCTU will be receiving the packet.

Cranberry & Dragonfruit:

1. Verify the port is assigned to the programmer (under Tools tab).
2. Upload using programer, NOT the button (Ctrl-Shift-U).
3. Once uploading is complete, the board will now be sending a packet of hard coded information.
3. The XBEE attached to XCTU will be receiving the packet.

# Expected Results (Read from received packet):
Note: These values are displayed in XCTU as hex values.

UART Test:
* The string "test yes"

Binary Test (Assuming you're following Schema 1):
* Some API packet coding identification
* Schema number: 01
* Hex code for the Microcontroller address
* Hex code for up time of the program
* Hex code for overflow (if occurred) otherwise: 00
* Hex code for n count: 0A
* Hex code for Battery mV: 01
* Hex code for Panel mV: 02
* Hex code for Pressure: 04
* Hex code for Temperature: 05
* Hex code for Humidity: 06
* Hex code for Solar Irradiance: 03
