/*********************************************
 *
 *    File: REIS_Weatherbox.ino
 *    REIS Weatherbox Firmware
 *
 *    The main driver file for the REIS Weatherbox
 *
 ********************************************/

/* Program Libraries */
#include "config.h"
#include "sensors.h"
#include "transmit.h"
#include "low_pass.h"
#include "schema.h"
#include "utilities.h"

/* Arudino Libraries */
#include <Wire.h>
#include <EEPROM.h>

/* External Libraries */
#include <SHT1x.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_INA219.h>
#include <Adafruit_BMP085.h>
#include <XBee.h>

/* Global Variable for Packet (BAD FIND ALTERNATIVE) */
#ifdef UART
    uint8_t G_packet[MAX_SIZE];
#elif defined(BINARY)
    schema_3 *G_packet;
#endif

/* Global Function Pointers */
void (*Sensors_init)(void);
int (*Sensors_sampleBatterymV)(void);
int (*Sensors_samplePanelmV)(void);
int (*Sensors_sampleSolarIrrmV)(void);
int (*Sensors_samplePressurepa)(void);
int (*Sensors_sampleHumiditypct)(void);
int (*Sensors_sampleTempdecic)(void);

/*********************************************
 *
 *    Name:        setup
 *    Returns:     Nothing
 *    Parameter:   Nothing
 *    Description: Runs once at the start of the sequence.
 *                     Used for initialization. Place all
 *                     init scripts here.
 * 
 ********************************************/
void setup(){

    /* Generation Check */
    Gen_config();

    /* Create Xbee Object */
    XBee xbee = XBee();

    /* Initialization */
    Sensors_init();
    Serial.begin(9600);
    xbee.begin(Serial);

    /* Packet Initialization */
#ifdef UART
    Packet_ClearUART(G_packet);
#elif defined(BINARY)
    /* Allocate memory for the struct */
    G_packet = (schema_3 *)malloc(sizeof(schema_3));
    Packet_ClearBIN(G_packet);
#endif
}

/*********************************************
 *
 *    Name:        loop
 *    Returns:     Nothing
 *    Parameter:   Nothing
 *    Description: Main program function, runs constantly.
 *                     Executed after setup(), and will
 *                     continue running indefinitely,
 *                     unless conditions stop it.
 * 
 ********************************************/
void loop(){


    /* Packet Construction */
#ifdef UART
    Packet_ConUART(G_packet);
#elif defined(BINARY)
    Packet_ConBIN(G_packet);
#endif

    /* Transmit Packet */
#ifdef UART
    Packet_TrnsmitUART(G_packet);
#elif defined(BINARY)
    Packet_TransmitBIN(G_packet);
#endif

    /* Clear Packet Buffer */
}
