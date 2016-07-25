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
#include "log.h"

/* Arudino Libraries */
#include <Wire.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

/* External Libraries */
#include <SHT1x.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_INA219.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_MPL115A2.h>
#include <Adafruit_ADS1015.h>
#include <HIH613x.h>
#include <XBee.h>

/* Global Xbee object */
XBee G_xbee = XBee();

#ifdef APPLE
schema_7 G_BINpacket;
#elif defined(CRANBERRY) || defined(DRAGONFRUIT)
schema_3 G_BINpacket;
#endif

/* Global for Filters */
LowPassFilter G_solar_filter;
LowPassFilter G_battery_filter;

/* Global Variable */
int G_count;

/* Global Function Pointers */
void (*Sensors_init)(void);
long (*Sensors_sampleBatterymV)(void);
long (*Sensors_samplePanelmV)(void);
long (*Sensors_sampleSolarIrrmV)(void);
long (*Sensors_samplePressurepa)(void);
long (*Sensors_sampleHumiditypct)(void);
long (*Sensors_sampleTempdecic)(void);
void (*Packet_Clear)(void);
void (*Packet_Con)(void);
void (*Packet_Transmit)(void);
void (*Normal_Routine)(int *count);

/* Software Serial */
SoftwareSerial mySerial(_PIN_XBEE_RX, _PIN_XBEE_TX);

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

    /* Initialization */
    Sensors_init();
    Serial.begin(9600);
    mySerial.begin(9600);
    G_xbee.begin(mySerial);

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
    /* Voltages are at a good level to operate normally */
    Normal_Routine(&G_count);
}
