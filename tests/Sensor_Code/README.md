# Sensor Code Test Directory

Used to test the sensor functions for each generation.  This contains the basic funtions and operations of the Sensor Module.  This ONLY tests the sensors on each board.

All test directories contain the Configuration Module.

# Tools

1. Arduino IDE
2. Programmer

# Obtaining Sensor Module

1. Pull/Download zip of Sensor_Code and the library directory, libraries
2. Put the libraries directory in the Arduino folder
   * Add contents to the libraries directory if a libraries directory already exists here.
   * This directory was made when installing and setting up the Arduino IDE.
3. Open the .ino file.
4. Navigate to the tab named config.h in Arduino IDE.
5. Comment out any other declared generation and uncomment the generation to be ran on.

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
2. Once uploading is complete, open Serial Monitor (Ctrl-Shift-M).
3. Sensor readings will appear here. New readings occur ~every 6 seconds.

Cranberry & Dragonfruit:

1. Verify the port is assigned to the programmer (under Tools tab).
2. Upload using programmer, NOT the button (Ctrl-Shift-U).
3. Once uploading is complete, switch the port to the FTDI device (under Tools tab).
4. Open Serial Monitor (Ctrl-Shift-M).
5. Sensor readings will appear here. New readings occur ~every 6 seconds.

# Averages of Expected Results (Inside SCEL room):

* Battery mV = ~4095 (Varies upon battery source level)
* SolarIrrmV = ~1908 (with lamp at full power and full exposure)
* Humiditypct = ~54 (slight exposure to lamp heat, but not direct)
* PanelmV = ~4050 (with lamp at full power and full exposure)
* Tempdecic = ~26 (slight exposure to lamp heat, but not direct)
* Pressure pa = ~101056
