#include "gd_dev_xbee.h"

void gd_dev_xbee_open(void)
{
    soft_serial.begin(9600);
    xbee.begin(soft_serial);
    // Enable voltage regulator pin to power the Xbee 
    digitalWrite(3, HIGH);

    // Configure pin connected to DTR on XBee
    // Since in router mode we don't care what the output is
    // so we can drive this signal LOW by default
    pinMode(A1, OUTPUT);
    digitalWrite(A1, LOW);

    // Configure pin connected to RSSI on XBee
    // Since RSSI pin is set to output on XBee, set the RSSI pin to
    // input on MCU
    pinMode(A2, INPUT);

    // Configure pin connected to XBee sleep pin on XBee
    // Since the XBee sleep pin is set to output on XBee, set 
    // the pin to input on MCU
    pinMode(A3, INPUT);
}

int gd_dev_xbee_avail(void)
{
    return Serial.available();
}

int gd_dev_xbee_read(void)
{
    return Serial.read();
}

void gd_dev_xbee_write(uint8_t *data, int data_len)
{
    XBeeAddress64 addr64 = XBeeAddress64(0, 0);
    ZBTxRequest zbtx = ZBTxRequest(addr64, data, data_len);

    xbee.send(zbtx);
}

