/*******************************************
 *
 *    File: sensors.h
 *    REIS Weatherbox Firmware
 *    
 *    Header file for Sensor functions
 *
 ******************************************/

/* Necessary Libraries */
#include "apple.h"               //To be replaced by Gen. Config. File
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

/* Sensor Initialization */
void Sensors_init(void);

/* Sampling Functions */
int Sensors_sampleBatterymV(void);
int Sensors_samplePanelmV(void);
int Sensors_sampleSolarIrrmV(void);
int Sensors_samplePressurepa(void);
int Sensors_sampleHumiditypct(void);
int Sensors_sampleTempdecic(void);
#endif
