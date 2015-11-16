/*******************************************
 *
 *    File: sensors.h
 *    REIS Weatherbox Firmware
 *    
 *    Header file for Sensor functions
 *
 ******************************************/

/* Program Libraries */
#include "config.h"

/* External Libraries */
#include <SHT1x.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_INA219.h>
#include <Adafruit_BMP085.h>

/* Check for previous includes */
#ifndef SENSORS_H
#define SENSORS_H

/* Create instances of objects */
extern OneWire oneWire1;
extern DallasTemperature dallas_amb_sen;

extern OneWire oneWire2;
extern DallasTemperature dallas_roof_sen;

extern SHT1x sht1x;

extern Adafruit_BMP085 bmp085;
extern Adafruit_INA219 ina219_Solar;

/******************************************
 *
 *    Apple
 *
 *****************************************/

/* Sensor Initialization */
void a_Sensors_init(void);

/* Sampling Functions */
int a_Sensors_sampleBatterymV(void);
int a_Sensors_samplePanelmV(void);
int a_Sensors_sampleSolarIrrmV(void);
int a_Sensors_samplePressurepa(void);
int a_Sensors_sampleHumiditypct(void);
int a_Sensors_sampleTempdecic(void);

/******************************************
 *
 *    Cranberry
 *
 *****************************************/

/* Sensor Initialization */

/* Sampling Functions */


/******************************************
 *
 *    Dragonfruit
 *
 *****************************************/

/* Sensor Initialization */

/* Sampling Functions */

#endif
