/*******************************
 *
 * File: ga_dev_apogee_BM180_pressure.h
 *
 * Contains prototypes for bmp085 sensor functions
 *
 ******************************/

#include <Arduino.h>
#include <Adafruit_BMP085.h>

#ifndef GA_DEV_APOGEE_BMP180_PRESSURE_H
#define GA_DEV_APOGEE_BMP180_PRESSURE_H
void ga_dev_apogee_BMP180_pressure_open(void);
uint32_t ga_dev_apogee_BMP180_pressure_read(void);
#endif
