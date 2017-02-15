#include "gg_dev_xbee.h"

void gg_dev_xbee_open(void)
{
    soft_serial.begin(9600);
    xbee.begin(soft_serial);
}

int gg_dev_xbee_avail(void)
{
    return Serial.available();
}

int gg_dev_xbee_read(void)
{
    return Serial.read();
}

void gg_dev_xbee_write(uint8_t *data, int data_len)
{
    XBeeAddress64 addr64 = XBeeAddress64(0, 0);
    ZBTxRequest zbtx = ZBTxRequest(addr64, data, data_len);

    xbee.send(zbtx);
}
