/*******************************
 *
 * File: gg_dev_digi_xbee.cpp
 *
 * This module is a driver for the XBee Transceiver. This
 * is used to radio communication with the server
 *
 * Product page: http://www.digi.com/support/productdetail?pid=4549
 * Datasheet: http://www.digi.com/resources/documentation/digidocs/PDFs/90000976.pdf
 *
 ******************************/

#include "gg_dev_digi_xbee.h"

/******************************
 *
 * Name:        gg_dev_digi_xbee_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize XBee pins
 *
 ******************************/

void gg_dev_digi_xbee_open(void)
{
    Serial1.begin(9600);
    xbee.begin(Serial1);
}

/******************************
 *
 * Name:        gg_dev_digi_xbee_avail
 * Returns:     0 if busy, 1 if available
 * Parameter:   Nothing
 * Description: Check to see if the XBee is busy
 *
 ******************************/

int gg_dev_digi_xbee_avail(void)
{
    return Serial1.available();
}

/******************************
 *
 * Name:        gg_dev_digi_xbee_read
 * Returns:     Data from XBee
 * Parameter:   Nothing
 * Description: Read data from the XBee
 *
 ******************************/

int gg_dev_digi_xbee_read(void)
{
    return Serial1.read();
}

/******************************
 *
 * Name:        gc_dev_digi_xbee_write
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Transmits packet through XBee
 *
 ******************************/

void gg_dev_digi_xbee_write(uint8_t *data, int data_len)
{
    XBeeAddress64 addr64 = XBeeAddress64(0x13a200, 0x4166d10e);
    ZBTxRequest zbtx = ZBTxRequest(addr64, data, data_len);

    xbee.send(zbtx);
}
