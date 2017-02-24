/*******************************
 *
 * File: ga_dev_batt.h
 *
 * Contains prototypes for bmp085 sensor functions
 *
 ******************************/

#include <Arduino.h>
#include <Adafruit_BMP085.h>

#ifndef GA_DEV_BMP085_H
#define GA_DEV_BMP085_H
void ga_dev_bmp085_open(void);
int ga_dev_bmp085_avail(void);
uint32_t ga_dev_bmp085_read_press(void);
int16_t ga_dev_bmp085_read_temp(void);
#endif
