# REIS SCEL Firmware Main Directory

Contains the full integration of the modules for the finalized firmware for the operation of the Weatherboxes.

Modules:
* Sensor
* Transmit
* Configuration
* Utilities

# Obtaining Firmware

1. Pull/Download zip of REIS_Weatherbox and the library directory, libraries
2. Put the libraries directory in the Arduino folder
   * Add contents to the libraries directory if a libraries directory already exists here.
   * This directory was made when installing and setting up the Arduino IDE.
3. Open the .ino file.
4. Navigate to the tab named config.h in Arduino IDE.
5. Comment out any other declared generation and uncomment the generation to be ran on.
6. Uncomment the method of transmission you wish to use and comment out the other method (UART v.s. Binary).

# Set-Up Arduino IDE
1. Under Tools check:
   * Board is set correctly (usually Arduino UNO).
   * Port is set correctly (the USB with the programmer plugged into it).
   * Programmer is set correctly (usually AVRISP mkII).
2. Do a test compile to ensure the libraries are found correctly and no other errors exist.
3. Plug Programmer into board.

# Uploading Firmware
Apple:

1. Click the upload button (arrow pointing to the right, next to the compile button).
2. Once uploading is complete, the board is ready for deployment.

Cranberry & Dragonfruit:

1. Upload using programmer, NOT the button (Ctrl-Shift-U).
2. Once uploading is complete, the board is ready for deployment.
