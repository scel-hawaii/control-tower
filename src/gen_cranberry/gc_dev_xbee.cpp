#include "gc_dev_xbee.h"

void gc_dev_xbee_open(void)
{
    soft_serial.begin(9600);
    xbee.begin(soft_serial);

    /* Enable the XBee voltage regulator pin to power XBee */
    digitalWrite(3, HIGH);
}

int gc_dev_xbee_avail(void)
{
    return Serial.available();
}

int gc_dev_xbee_read(void)
{
    return Serial.read();
}

void gc_dev_xbee_write(uint8_t *data, int data_len)
{
    XBeeAddress64 addr64 = XBeeAddress64(0, 0);
    ZBTxRequest zbtx = ZBTxRequest(addr64, data, data_len);

    xbee.send(zbtx);
}
