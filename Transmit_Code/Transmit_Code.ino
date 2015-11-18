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

/* Arduino Libraries */
#include <EEPROM.h>

/* External Libraries */
#include <XBee.h>
#include <stdint.h>

/* Global Variable for Packet (BAD FIND ALTERNATIVE) */
#ifdef UART
    uint8_t G_packet[MAX_SIZE];
#elif defined(BINARY)
    schema_3 *G_packet;
#endif

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

    /* Create Xbee Object */
    XBee xbee = XBee();
    Serial.begin(9600);
    xbee.begin(Serial);

    /* Packet initialization */
#ifdef UART
    Packet_ClearUART(G_packet);
#elif defined(BINARY)
    /* Allocate memory for the struct */
    G_packet = (schema_3 *)malloc(sizeof(schema_3));
    Packet_ClearBIN(G_packet);
#endif

    /* Generate a test packet */
#ifdef UART
    Test_Packet_GenUART(G_packet);
#elif defined(BINARY)
    Test_Packet_GenBIN(G_packet);
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
    Packet_TransmitUART(G_packet);
#elif defined(BINARY)
    Packet_TransmitBIN(G_packet);
#endif

    /* Debug: Notify packet was transmitted */
    /* The F() keeps the char array in PROGMEM, using only */
    /*      one byte of ram */
    Serial.println(F("\nPacket Transmitted.\n"));

    /* Necessary delay to prevent overloading receiving end */
    delay(5000);
Serial.println(F("Here"));

    /* Clean-up the Serial Monitor */
    Serial.flush();
}
