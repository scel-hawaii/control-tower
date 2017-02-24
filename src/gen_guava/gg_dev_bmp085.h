/*******************************
 *
 * File: gg_dev_batt.h
 *
 * Contains prototypes for bmp085 sensor functions
 *
 ******************************/

#include <Arduino.h>
#include <Adafruit_BMP085.h>

#ifndef gg_DEV_BMP085_H
#define gg_DEV_BMP085_H
void gg_dev_bmp085_open(void);
int gg_dev_bmp085_avail(void);
uint32_t gg_dev_bmp085_read_press(void);
int16_t gg_dev_bmp085_read_temp(void);
#endif
