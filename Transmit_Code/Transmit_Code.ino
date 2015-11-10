/*******************************************
 *
 *    File: Transmit_Code.ino
 *    REIS Weatherbox Firmware
 *    
 *    Test .ino to check Transmission functions
 *
 ******************************************/

/* Necessary Libraries */
#include "transmit.h"

/* Arduino Libraries */
#include <XBee.h>

/* Macros */
#define MAX_SIZE 200

/* Global Variable for Packet (BAD FIND ALTERNATIVE) */
uint8_t G_packet[MAX_SIZE];

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

    /* Variables */
    int i = 0;

    /* Packet initialization */
    for(i = 0; i < MAX_SIZE; i++){
      G_packet[i] = '\0';
    }

    /* Create Xbee Object */
    XBee xbee = XBee();
    Serial.begin(9600);
    xbee.begin(Serial);

    /* Generate a test packet */
    Test_Packet_Gen(G_packet);
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
    Packet_Transmit(G_packet);

    /* Debug: Notify packet was transmitted */
    Serial.print("\nPacket Transmitted.\n");

    /* Necessary delay to prevent overloading receiving end */
    delay(5000);

    /* Clean-up the Serial Monitor */
    Serial.flush();
}
