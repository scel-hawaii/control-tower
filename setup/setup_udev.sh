# Setup udev rules to symlink USB ftdi dongle
# 
# Example:
# $ cat /etc/udev/ftdi.rules 
# SUBSYSTEMS=="usb", KERNEL=="ttyUSB*", ATTRS{idVendor}=="0403", ATTRS{idProduct}=="6001", ATTRS{serial}=="FTDEN97D", SYMLINK+="ttyFTDI0"
# SUBSYSTEMS=="usb", KERNEL=="ttyUSB*", ATTRS{idVendor}=="0403", ATTRS{idProduct}=="6001", ATTRS{serial}=="A600b30P", SYMLINK+="ttyFTDI1"
# SUBSYSTEMS=="usb", KERNEL=="ttyUSB*", ATTRS{idVendor}=="0403", ATTRS{idProduct}=="6001", ATTRS{serial}=="A600bexU", SYMLINK+="ttyFTDI2"
# SUBSYSTEMS=="usb", KERNEL=="ttyUSB*", ATTRS{idVendor}=="0403", ATTRS{idProduct}=="6001", ATTRS{serial}=="FTFMSA54", SYMLINK+="ttyFTDI3"
# SUBSYSTEMS=="usb", KERNEL=="ttyUSB*", ATTRS{idVendor}=="0403", ATTRS{idProduct}=="6001", ATTRS{serial}=="FTFMUW4A", SYMLINK+="ttyFTDI4"
#
#
# Original stackexchange website:  http://stackoverflow.com/questions/9183880/how-to-find-out-which-usb-rs232-device-is-on-which-tty
#
#
# TODO: Implement a script to automatically set this up for a user
#           * Scan dmesg and wait for a USB dongle to be insertted 
#           * Get the device ID and then mount it





