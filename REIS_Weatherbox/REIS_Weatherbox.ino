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

    /* Health Check */
    initHealthsamples();
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

    /* Variables to hold Sensor Readings */
    int BatterymV = 0;
    int SolarIrrmV = 0;
    int Humiditypct = 0;
    int PanelmV = 0;
    int Pressurepa = 0;
    int Tempdecic = 0;

    /* Sample Sensors */
    BatterymV = (*Sensors_sampleBatterymV)();
    SolarIrrmV = (*Sensors_sampleSolarIrrmV)();
    Humiditypct = (*Sensors_sampleHumiditypct)();
    PanelmV = (*Sensors_samplePanelmV)();
    Pressurepa = (*Sensors_samplePressurepa)();
    Tempdecic = (*Sensors_samplePressurepa)();

    /* Packet Construction */

    /* Transmit Packet */

    /* Clear Packet Buffer */

}
