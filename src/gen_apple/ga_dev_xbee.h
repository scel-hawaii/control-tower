/*******************************
 *
 * File: ga_dev_xbee.h
 *
 * Contains prototypes for XBee Transceiver functions
 *
 ******************************/

#include <Arduino.h>
#include <XBee.h>
#include <SoftwareSerial.h>

#define _GA_DEV_XBEE_BUFSIZE_ 150

#ifndef GA_DEV_XBEE
#define GA_DEV_XBEE
void ga_dev_xbee_open(void);
int ga_dev_xbee_avail(void);
int ga_dev_xbee_read(void);
void ga_dev_xbee_write(uint8_t* data, int data_len);

static XBee xbee = XBee();

const byte rx_pin = 2;
const byte tx_pin = 9;
static SoftwareSerial soft_serial(rx_pin, tx_pin);
#endif
