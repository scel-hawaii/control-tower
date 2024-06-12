/*******************************
 *
 * File: ga_dev_digi_xbee.h
 *
 * Contains prototypes for XBee Transceiver functions
 *
 ******************************/

#include <Arduino.h>
#include <XBee.h>
#include <SoftwareSerial.h>

#define _GA_DEV_DIGI_XBEE_BUFSIZE_ 150

//FOR SLEEP FUNCTION
//#define XBEE_sleepPin 6
//#define SLEEP_COUNTER 0
//FOR SLEEP FUNCTION

#ifndef GA_DEV_DIGI_XBEE
#define GA_DEV_DIGI_XBEE
void ga_dev_digi_xbee_open(void);
int ga_dev_digi_xbee_avail(void);
int ga_dev_digi_xbee_read(void);
void ga_dev_digi_xbee_write(uint8_t* data, int data_len);
void xbeesleep(void);
void xbeewake();

static XBee xbee = XBee();

const byte rx_pin = 2;

#ifndef SEN_STUB
const byte tx_pin = 9;
#else
const byte tx_pin = 3;
#endif

static SoftwareSerial soft_serial(rx_pin, tx_pin);
#endif