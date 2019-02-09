/*******************************
 *
 * File: gg_dev_digi_xbee.cpp
 *
 * This module is a driver for the XBee Transceiver. This
 * is used to radio communication with the server
 *
 * Product page: http://www.digi.com/support/productdetail?pid=4549
 * Datasheet: http://www.digi.com/resources/documentation/digidocs/PDFs/90000976.pdf
 *
 ******************************/

#include "gg_dev_digi_xbee.h"

/******************************
 *
 * Name:        gg_dev_digi_xbee_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize XBee pins
 *
 ******************************/

void gg_dev_digi_xbee_open(void)
{
    soft_serial.begin(9600);
    xbee.begin(soft_serial);
}

/******************************
 *
 * Name:        gg_dev_digi_xbee_avail
 * Returns:     0 if busy, 1 if available
 * Parameter:   Nothing
 * Description: Check to see if the XBee is busy
 *
 ******************************/

int gg_dev_digi_xbee_avail(void)
{
    return Serial.available();
}

/******************************
 *
 * Name:        gg_dev_digi_xbee_read
 * Returns:     Data from XBee
 * Parameter:   Nothing
 * Description: Read data from the XBee
 *
 ******************************/

int gg_dev_digi_xbee_read(void)
{
    return Serial.read();
}


void flashLed(int pin, int times, int wait){
  for(int i = 0; i< times; i++){
    digitalWrite(pin,HIGH);
    delay(wait);
    digitalWrite(pin,LOW);

    if(i+1 < times){
      delay(wait);
    }
  }

}

/******************************
 *
 * Name:        gc_dev_digi_xbee_write
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Transmits packet through XBee
 *
 ******************************/

void gg_dev_digi_xbee_write(uint8_t *data, int data_len)
{
    XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x406CB708);
    ZBTxRequest zbtx = ZBTxRequest(addr64, data, data_len);

    xbee.send(zbtx);

#ifdef DEBUG

    pinMode(statusLed,OUTPUT);
    pinMode(errorLed,OUTPUT);

    ZBTxStatusResponse txStatus = ZBTxStatusResponse();

    // after sending a tx request we expect a status response
    // wait up to hald second for the status response
    if(xbee.readPacket(500)){

      // should be a znet tx status
      if(xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE){
        xbee.getResponse().getZBTxStatusResponse(txStatus);

        // get the delivery status, the fifth byte
        if(txStatus.getDeliveryStatus() == SUCCESS) {
          // success
          flashLed(statusLed, 5, 100);

        } else {
          // the remote did not receive our packet
          flashLed(errorLed, 3, 500);
        }
      }
    }
#endif
}
