/*
 * Tranmissiion Test
*/

/* Program Libraries */
#include "transmit.h"

/* Arduino Libraries */
#include <XBee.h>

/* Macros */
#define MAX_SIZE 200

/* Global Variable for Packet (BAD FIND ALTERNATIVE) */
uint8_t packet[MAX_SIZE];

void setup(){
    Serial.begin(9600);
    Packet_Transmit(packet);
}

void loop(){
    Packet_Transmit(packet);
    Serial.print("Packet Transmitted.\n");
    delay(5000);
}
