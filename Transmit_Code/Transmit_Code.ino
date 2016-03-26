/*******************************************
 *
 *    File: Transmit_Code.ino
 *    REIS Weatherbox Firmware
 *    
 *    Test .ino to check Transmission functions
 *
 ******************************************/

/* Program Libraries */
#include "transmit.h"
#include "config.h"

/* Arduino Libraries */
#include <EEPROM.h>
#include <SoftwareSerial.h>

/* External Libraries */
#include <XBee.h>
#include <stdint.h>
#include <overflow_checker.h>

/* Global Variable for Packet */
uint8_t G_UARTpacket[MAX_SIZE];
  
/* Create Xbee Object */
XBee G_xbee = XBee();

#ifdef APPLE
schema_2 G_BINpacket;
#elif defined(CRANBERRY) || defined(DRAGONFRUIT)
schema_1 G_BINpacket;
#endif

/* Software Serial */
SoftwareSerial mySerial(_PIN_XBEE_RX, _PIN_XBEE_TX);

/******************************************
 *
 *   Name:        setup
 *   Returns:     Nothing
 *   Parameter:   Nothing
 *   Description: Runs once at the start of the sequence.
 *                    Used for initialization. Place all
 *                    init scripts here.
 *
 *****************************************/
void setup(){

    /* Serial Initialization*/
    Serial.begin(9600);
    mySerial.begin(9600);
    G_xbee.begin(Serial);

#ifndef APPLE
    pinMode(_PIN_XBEE_EN, OUTPUT);
#endif

    /* Packet initialization */
#ifdef UART
    Packet_ClearUART();
#elif defined(BINARY)
    Packet_ClearBIN();
#endif

    /* Generate a test packet */
#ifdef UART
    Test_Packet_GenUART();
#elif defined(BINARY)
    Test_Packet_GenBIN();
#endif
}

/******************************************
 *
 *   Name:        loop
 *   Returns:     Nothing
 *   Parameter:   Nothing
 *   Description: Main program function, runs constantly.
 *                    Executed after setup(), and will
 *                    continue running indefinitely,
 *                    unless conditions stop it.
 *
 *****************************************/
void loop(){

    /* Transmit the packet */
#ifdef UART
    Packet_TransmitUART();
#elif defined(BINARY)
    Packet_TransmitBIN();
#endif

    /* Debug: Notify packet was transmitted */
    /* The F() keeps the char array in PROGMEM, using only */
    /*      one byte of ram */
#ifdef DEBUG_S
    Serial.println(F("\nPacket Transmitted.\n"));
#endif

    /* Necessary delay to prevent overloading receiving end */
    delay(5000);
}
