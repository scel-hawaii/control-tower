#include "ga23_dev_xbee.h"

void ga23_dev_xbee_open(void)
{
    Serial.begin(9600);
    xbee.begin(Serial);
}

int ga23_dev_xbee_avail(void)
{
    return Serial.available();
}

int ga23_dev_xbee_read(void)
{
    return Serial.read();
}

void ga23_dev_xbee_write(uint8_t packet)
{

}

