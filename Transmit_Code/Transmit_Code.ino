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
#include "schema.h"
#include "packet_binary.h"
#include "sensors.h"
#include <overflow_checker.h>

/* Arduino Libraries */
#include <XBee.h>
#include <SHT1x.h>
#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <Adafruit_INA219.h>
#include <Adafruit_BMP085.h>

/* Macros */
#define MAX_SIZE 200

/* Global Variable for Packet (BAD FIND ALTERNATIVE) */
//uint8_t packet[MAX_SIZE];

/******************************************
 *
 *   Name:        setup
 *   Returns:     Nothing
 *   Parameter:   Nothing
 *   Description: Runs once at the start of the sequence.
 *                    Used for initialization. Place all
 *                    Init scripts here.
 *
 *****************************************/
void setup(){

    /* Variables */
    int i = 0;

    /* Packet initialization */
    for(i = 0; i < MAX_SIZE; i++){
      packet[i] = '\0';
    }

    /* Create Xbee Object */
    XBee xbee = XBee();
    Serial.begin(9600);
<<<<<<< HEAD
//    Packet_Transmit(packet);

    /* Packet Binary Testing */
    schema_3 packet;

    clear_packet();
    packet.schema = 3;
=======
    xbee.begin(Serial);

    /* Generate a test packet */
    Test_Packet_Gen(packet);
>>>>>>> 31ae04fcfc7704652e4c697374e4559eda660fbd
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
<<<<<<< HEAD
//    Packet_Transmit(packet);
//    Serial.print("Packet Transmitted.\n");
//    delay(5000);

    samplePacketBinary();
    Serial.print("Packet sampled.\n");
=======

    /* Transmit the packet */
    Packet_Transmit(packet);

    /* Debug: Notify packet was transmitted */
    Serial.print("\nPacket Transmitted.\n");

    /* Necessary delay to prevent overloading receiving end */
>>>>>>> 31ae04fcfc7704652e4c697374e4559eda660fbd
    delay(5000);

    /* Clean-up the Serial Monitor */
    Serial.flush();
}
