/*******************************************
 *
 *    File: sensors.h
 *    REIS Weatherbox Firmware
 *    
 *    Header file for Sensor functions
 *
 ******************************************/

/* External Libraries */
#include <SHT1x.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_INA219.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_MPL115A2.h>
#include <Adafruit_ADS1015.h>
#include <HIH613x.h>

/* Check for previous includes */
#ifndef SENSORS_H
#define SENSORS_H

/* Create instances of objects */
extern OneWire oneWire;
extern DallasTemperature dallas_amb_sen;

extern SHT1x sht1x;

extern Adafruit_BMP085 bmp085;
extern Adafruit_INA219 ina219_Solar;
extern Adafruit_MPL115A2 mpl115a2;
extern Adafruit_ADS1115 PyroADC_C;
extern HIH613x hih6131;

/******************************************
 *
 *    Apple
 *
 *****************************************/

/* Sensor Initialization */
void a_Sensors_init(void);

/* Sampling Functions */
long a_Sensors_sampleBatterymV(void);
long a_Sensors_samplePanelmV(void);
long a_Sensors_sampleSolarIrrmV(void);
long a_Sensors_samplePressurepa(void);
long a_Sensors_sampleHumiditypct(void);
long a_Sensors_sampleTempdecic(void);
long a_Sensors_sampleRoofTempdecic(void);

/******************************************
 *
 *    Cranberry
 *
 *****************************************/

/* Sensor Initialization */
void c_Sensors_init(void);

/* Sampling Functions */
long c_Sensors_sampleBatterymV(void);
long c_Sensors_samplePanelmV(void);
long c_Sensors_sampleSolarIrrmV(void);
long c_Sensors_samplePressurepa(void);
long c_Sensors_sampleHumiditypct(void);
long c_Sensors_sampleTempdecic(void);


/******************************************
 *
 *    Dragonfruit
 *
 *****************************************/

/* Sensor Initialization */
void d_Sensors_init(void);

/* Sampling Functions */
long d_Sensors_sampleBatterymV(void);
long d_Sensors_samplePanelmV(void);
long d_Sensors_sampleSolarIrrmV(void);
long d_Sensors_samplePressurepa(void);
long d_Sensors_sampleHumiditypct(void);
long d_Sensors_sampleTempdecic(void);

#endif
