/*******************************
 *
 * File: gc_dev_digi_xbee.h
 *
 * Contains prototypes for XBee Transceiver functions
 *
 ******************************/

#include <Arduino.h>
#include <XBee.h>

#define _GG_DEV_DIGI_XBEE_BUFSIZE_ 150

#ifndef GG_DEV_DIGI_XBEE
#define GG_DEV_DIGI_XBEE
void gg_dev_digi_xbee_open(void);
int gg_dev_digi_xbee_avail(void);
int gg_dev_digi_xbee_read(void);
void gg_dev_digi_xbee_write(uint8_t* data, int data_len);

static XBee xbee = XBee();

#endif
