/*******************************
 *
 * File: gd_dev_xbee.h 
 *
 * Contains prototypes for the XBee module 
 *
 ******************************/

#include <Arduino.h>
#include <XBee.h>
#include <SoftwareSerial.h>

#define _GD_DEV_XBEE_BUFSIZE_ 150

#ifndef GD_DEV_XBEE
#define GD_DEV_XBEE
void gd_dev_xbee_open(void);
int gd_dev_xbee_avail(void);
int gd_dev_xbee_read(void);
void gd_dev_xbee_write(uint8_t* data, int data_len);

static XBee xbee = XBee();

const byte rx_pin = 2;
const byte tx_pin = 8;
static SoftwareSerial soft_serial(rx_pin, tx_pin);
#endif
