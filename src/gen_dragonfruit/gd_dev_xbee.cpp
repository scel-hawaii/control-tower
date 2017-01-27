/*******************************
 *
 * File: gd_dev_xbee.cpp
 *
 * This module is a driver for the XBee module. It uses the XBee 
 * to construct and transmit sensor data in packets.
 *
 * Product page: http://www.digi.com/support/productdetail?pid=4549
 * Datasheet: http://www.digi.com/resources/documentation/digidocs/PDFs/90000976.pdf
 *
 ******************************/

#include "gd_dev_xbee.h"

/******************************
 * 
 * Name:        gd_dev_xbee_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize XBee module 
 * 
 ******************************/
void gd_dev_xbee_open(void)
{
    soft_serial.begin(9600);
    xbee.begin(soft_serial);
    // Enable voltage regulator pin to power the Xbee 
    digitalWrite(3, HIGH);

    // Configure pin connected to DTR on XBee
    // Since in router mode we don't care what the output is
    // so we can drive this signal LOW by default
    pinMode(A1, OUTPUT);
    digitalWrite(A1, LOW);

    // Configure pin connected to RSSI on XBee
    // Since RSSI pin is set to output on XBee, set the RSSI pin to
    // input on MCU
    pinMode(A2, INPUT);

    // Configure pin connected to XBee sleep pin on XBee
    // Since the XBee sleep pin is set to output on XBee, set 
    // the pin to input on MCU
    pinMode(A3, INPUT);
}

/******************************
 * 
 * Name:        gd_dev_xbee_avail
 * Returns:     The number of bytes available to read 
 * Parameter:   Nothing
 * Description: Number of characters available for reading from the serial port 
 * 
 ******************************/
int gd_dev_xbee_avail(void)
{
    return Serial.available();
}

/******************************
 * 
 * Name:        gd_dev_xbee_read
 * Returns:     The first byte of incoming serial data available
 *              (or -1 if no data is available)
 * Parameter:   Nothing
 * Description: Readings incoming serial data
 * 
 ******************************/
int gd_dev_xbee_read(void)
{
    return Serial.read();
}

/******************************
 * 
 * Name:        gd_dev_xbee_write
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Transmit packet through XBee
 * 
 ******************************/
void gd_dev_xbee_write(uint8_t *data, int data_len)
{
    // Specify the address of the remote XBee
    XBeeAddress64 addr64 = XBeeAddress64(0, 0);

    // Create a TX request
    ZBTxRequest zbtx = ZBTxRequest(addr64, data, data_len);

    // Send request
    xbee.send(zbtx);
}

