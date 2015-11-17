/*******************************************
 *
 *    File: Transmit_Code.ino
 *    REIS Weatherbox Firmware
 *    
 *    Test .ino to check Transmission functions
 *
 ******************************************/

/* Program Libraries */
//#include "sensors.h"
#include "transmit.h"
#include "schema.h"
#include "config.h"

/* Arduino Libraries */
#include <Wire.h>

/* External Libraries */
#include <SHT1x.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_INA219.h>
#include <Adafruit_BMP085.h>
#include <XBee.h>
#include <EEPROM.h>

/* Global Variable for Packet (BAD FIND ALTERNATIVE) */
#ifdef UART
    uint8_t G_packet[MAX_SIZE];
#elseif BINARY
    schema_3 G_packet;
#endif

/* Global function pointers */
void (*Sensors_init)(void);
int (*Sensors_sampleBatterymV)(void);
int (*Sensors_samplePanelmV)(void);
int (*Sensors_sampleSolarIrrmV)(void);
int (*Sensors_samplePressurepa)(void);
int (*Sensors_sampleHumiditypct)(void);
int (*Sensors_sampleTempdecic)(void);

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

    /* Generation Configuration */
    Gen_config();
    
    /* Packet initialization */
#ifdef UART
    Packet_ClearUART(G_packet);
#elseif BINARY
    Packet_ClearBIN(G_packet);
#endif

    /* Create Xbee Object */
    XBee xbee = XBee();
    Serial.begin(9600);
    xbee.begin(Serial);

    /* Generate a test packet */
#ifdef UART
    Test_Packet_GenUART(G_packet);
#elseif
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
#elseif BINARY
    Packet_TransmitBIN(G_packet);
#endif

    /* Debug: Notify packet was transmitted */
    Serial.print("\nPacket Transmitted.\n");

    /* Necessary delay to prevent overloading receiving end */
    delay(5000);

    /* Clean-up the Serial Monitor */
    Serial.flush();
}
