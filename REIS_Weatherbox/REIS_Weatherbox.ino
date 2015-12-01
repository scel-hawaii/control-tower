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

/* Global Variable for Packet  */
uint8_t G_UARTpacket[MAX_SIZE];
schema_3 G_BINpacket;

/* Global Function Pointers */
void (*Sensors_init)(void);
int (*Sensors_sampleBatterymV)(void);
int (*Sensors_samplePanelmV)(void);
int (*Sensors_sampleSolarIrrmV)(void);
int (*Sensors_samplePressurepa)(void);
int (*Sensors_sampleHumiditypct)(void);
int (*Sensors_sampleTempdecic)(void);
void (*Packet_Clear)(void);
void (*Packet_Con)(void);
void (*Packet_Transmit)(void);

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

    /* Transmission Method Check */
    Transmit_config();

    /* Create Xbee Object */
    XBee xbee = XBee();

    /* Initialization */
    Sensors_init();
    Serial.begin(9600);
    xbee.begin(Serial);
    initHealthSamples();

    /* Packet Initialization */
    Packet_Clear();
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
    
    /* Variable Initialization */
    int count = 0;  //To be used as a poll counter

    /* Check Health */

    /* Run appropriate routine */
    Normal_Routine(&count);
    //PowerSave_Routine();
}
