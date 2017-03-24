/*******************************
 *
 * File: ga_dev_apogee_BM180_pressure.h
 *
 * Contains prototypes for bmp085 sensor functions
 *
 ******************************/

#include <Arduino.h>
#include <Adafruit_BMP085.h>

#ifndef GA_DEV_APOGEE_BMP180_TEMPERATURE_H
#define GA_DEV_APOGEE_BMP180_TEMPERATURE_H
void ga_dev_apogee_BMP180_temperature_open(void);
int16_t ga_dev_apogee_BMP180_temperature_read(void);
#endif
