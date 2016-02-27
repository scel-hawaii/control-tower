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
#include <Adafruit_ADS1115.h>
#include <HIH613x.h>
#include <MCP342X.h>

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
extern Adafruit_MPL115A2 mpl115a2;
extern Adafruit_ADS1115 PyroADC_C;
extern MCP342X PyroADC_D;
extern HIH613x hih6131;

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
void c_Sensors_init(void);

/* Sampling Functions */
int c_Sensors_sampleBatterymV(void);
int c_Sensors_samplePanelmV(void);
int c_Sensors_sampleSolarIrrmV(void);
int c_Sensors_samplePressurepa(void);
int c_Sensors_sampleHumiditypct(void);
int c_Sensors_sampleTempdecic(void);


/******************************************
 *
 *    Dragonfruit
 *
 *****************************************/

/* Sensor Initialization */
void d_Sensors_init(void);

/* Sampling Functions */
int d_Sensors_sampleBatterymV(void);
int d_Sensors_samplePanelmV(void);
int d_Sensors_sampleSolarIrrmV(void);
int d_Sensors_samplePressurepa(void);
int d_Sensors_sampleHumiditypct(void);
int d_Sensors_sampleTempdecic(void);

#endif
