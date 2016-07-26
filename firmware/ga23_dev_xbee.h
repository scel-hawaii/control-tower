#include <Arduino.h>
#include <XBee.h>

#ifndef GA23_DEV_XBEE
#define GA23_DEV_XBEE
void ga23_dev_xbee_open(void);
int ga23_dev_xbee_avail(void);
int ga23_dev_xbee_read(void);
void ga23_dev_xbee_write(void);

static XBee xbee = XBee();
#endif

