/*******************************
 *
 * File: gb_dev_digi_xbee.h
 *
 * Contains prototypes for XBee Transceiver functions
 *
 ******************************/

#include <Arduino.h>
#include <XBee.h>
#include <SoftwareSerial.h>

#define _GB_DEV_DIGI_XBEE_BUFSIZE_ 150

#ifndef GB_DEV_DIGI_XBEE
#define GB_DEV_DIGI_XBEE
void gb_dev_digi_xbee_open(void);
int gb_dev_digi_xbee_avail(void);
int gb_dev_digi_xbee_read(void);
void gb_dev_digi_xbee_write(uint8_t* data, int data_len);

static XBee xbee = XBee();

const byte rx_pin = 3;
const byte tx_pin = 4;
static SoftwareSerial soft_serial(rx_pin, tx_pin);
#endif
