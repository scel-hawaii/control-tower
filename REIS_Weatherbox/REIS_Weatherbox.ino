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
#include "schema.h"
#include "utilities.h"
#include "routines.h"

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

/* Global Variables for Packet  */
uint8_t G_UARTpacket[MAX_SIZE];
schema_3 G_BINpacket;
schema_health G_health;

/* Global for Filters */
LowPassFilter G_solar_filter;
LowPassFilter G_battery_filter;

/* Global Variable */
int G_count;

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
void (*Normal_Routine)(int *count);

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

    /* Variable Initialization */
    G_count = 0;

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

    /* Set Power State */
    pstate_system(_ACTIVE);

    /* Delay for configuration settings */
    delay(500);
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

    /*Check health & run appropriate routine */
    if(chkHealth() == NORMAL || chkHealth() == GOOD_SOLAR){

        /* Voltages are at a good level to operate normally */
        Normal_Routine(&G_count);
    }
    else{

        /* Voltages are not at a good level, operate in PowerSave */
        PowerSave_Routine();
    }
}
