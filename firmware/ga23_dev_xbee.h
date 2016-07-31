#include <Arduino.h>
#include <XBee.h>

#define _GA23_DEV_XBEE_BUFSIZE_ 150

#ifndef GA23_DEV_XBEE
#define GA23_DEV_XBEE
void ga23_dev_xbee_open(void);
int ga23_dev_xbee_avail(void);
int ga23_dev_xbee_read(void);
void ga23_dev_xbee_write(uint8_t payload[_GA23_DEV_XBEE_BUFSIZE_]);

static XBee xbee = XBee();
#endif

