#include <Arduino.h>
#include <XBee.h>
#include <SoftwareSerial.h>

#define _GA23_DEV_XBEE_BUFSIZE_ 150

#ifndef GA23_DEV_XBEE
#define GA23_DEV_XBEE
void ga23_dev_xbee_open(void);
int ga23_dev_xbee_avail(void);
int ga23_dev_xbee_read(void);
void ga23_dev_xbee_write(uint8_t* data, int data_len);

static XBee xbee = XBee();

const byte rx_pin = 2;
const byte tx_pin = 3;
static SoftwareSerial soft_serial(rx_pin, tx_pin);
#endif

