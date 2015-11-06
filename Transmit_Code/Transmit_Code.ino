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
    int i = 0;
    for(i = 0; i < MAX_SIZE; i++){
      packet[i] = '\0';
    }
    XBee xbee = XBee();
    Serial.begin(9600);
    xbee.begin(Serial);
    Test_Packet_Gen(packet);
}

void loop(){
    Packet_Transmit(packet);
    Serial.print("\nPacket Transmitted.\n");
    delay(5000);
    Serial.flush();
}
