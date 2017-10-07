/*******************************
 *
 * File: gc_dev_digi_xbee.cpp
 *
 * This module is a driver for sending heartbeat and sensor data
 * packetes through the XBee transceiver
 *
 * Product page: https://www.digi.com/support/productdetail?pid=4549
 * Datasheet: http://pub.ucpros.com/download/90000976_M.pdf?osCsid=qnnqnolev4428en839un930cq4
 *
 ******************************/

#include "gc_dev_digi_xbee.h"

/******************************
 *
 * Name:        gc_dev_xbee_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize XBee pins and VReg pin
 *
 ******************************/

void gc_dev_digi_xbee_open(void)
{
    soft_serial.begin(9600);
    xbee.begin(soft_serial);

    /* Enable the XBee voltage regulator pin to power XBee */
    digitalWrite(3, HIGH);
}

/******************************
 *
 * Name:        gc_dev_xbee_avail
 * Returns:     0 if busy, 1 if available
 * Parameter:   Nothing
 * Description: Check to see if the XBee is busy
 *
 ******************************/

int gc_dev_digi_xbee_avail(void)
{
    return Serial.available();
}

/******************************
 *
 * Name:        gc_dev_xbee_read
 * Returns:     Data from XBee
 * Parameter:   Nothing
 * Description: Read data from the XBee
 *
 ******************************/

int gc_dev_digi_xbee_read(void)
{
    return Serial.read();
}

/******************************
 *
 * Name:        gc_dev_xbee_write
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Transmits packet through XBee
 *
 ******************************/

void gc_dev_digi_xbee_write(uint8_t *data, int data_len)
{
    XBeeAddress64 addr64 = XBeeAddress64(0, 0);
    ZBTxRequest zbtx = ZBTxRequest(addr64, data, data_len);

    xbee.send(zbtx);
}
