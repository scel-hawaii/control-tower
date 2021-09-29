/*******************************
 *
 * File: ga_dev_digi_xbee.cpp
 *
 * This module is a driver for the XBee Transceiver. This
 * is used to radio communication with the server
 *
 * Product page:
 *
 ******************************/

#include "ga_dev_digi_xbee.h"

/******************************
 *
 * Name:        ga_dev_digi_xbee_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize XBee pins
 *
 ******************************/

void ga_dev_digi_xbee_open(void)
{
    soft_serial.begin(9600);
    xbee.begin(soft_serial);
}

/******************************
 *
 * Name:        ga_dev_digi_xbee_avail
 * Returns:     0 if busy, 1 if available
 * Parameter:   Nothing
 * Description: Check to see if the XBee is busy
 *
 ******************************/

int ga_dev_digi_xbee_avail(void)
{
    return Serial.available();
}

/******************************
 *
 * Name:        ga_dev_digi_xbee_read
 * Returns:     Data from XBee
 * Parameter:   Nothing
 * Description: Read data from the XBee
 *
 ******************************/

int ga_dev_digi_xbee_read(void)
{
    return Serial.read();
}

/******************************
 *
 * Name:        ga_dev_digi_xbee_write
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Transmits packet through XBee
 *
 ******************************/

void ga_dev_digi_xbee_write(uint8_t *data, int data_len)
{
    XBeeAddress64 addr64 = XBeeAddress64(0, 0);
    ZBTxRequest zbtx = ZBTxRequest(addr64, data, data_len);

    xbee.send(zbtx);
}


//FOR SLEEP FUNCTION
/******************************
 *
 * Name:        ga_dev_digi_xbee_sleep
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Puts XBee in sleep mode
 *
 ******************************/

//void xbeesleep() {
  //Serial.println("XBEE IS NOW ASLEEP");   
 //delay (3000); 
 // pinMode (XBEE_sleepPin,OUTPUT);    // put XBee to sleep0
 // digitalWrite(XBEE_sleepPin,HIGH);  // Setting this pin to LOW turns off the pull up resistor, thus saving precious current
//}

/******************************
 *
 * Name:        ga_dev_digi_xbee_wake
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Wakes XBee up from sleep mode
 *
 ******************************/

//void xbeewake() {
 // Serial.println("XBEE IS NOW AWAKE");    
//  pinMode(XBEE_sleepPin,OUTPUT);   // Set the "wake-up pin" to output
//  digitalWrite(XBEE_sleepPin,LOW); // wake-up XBee
//  delay(1000); //make sure that XBee is ready
//}

//FOR SLEEP FUNCTION