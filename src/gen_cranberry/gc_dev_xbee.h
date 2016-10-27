#include <Arduino.h>
#include <XBee.h>
#include <SoftwareSerial.h>

#define _GC_DEV_XBEE_BUFSIZE_ 150

#ifndef GC_DEV_XBEE
#define GC_DEV_XBEE
void gc_dev_xbee_open(void);
int gc_dev_xbee_avail(void);
int gc_dev_xbee_read(void);
void gc_dev_xbee_write(uint8_t* data, int data_len);

static XBee xbee = XBee();

const byte rx_pin = 2;
const byte tx_pin = A3;
static SoftwareSerial soft_serial(rx_pin, tx_pin);
#endif
