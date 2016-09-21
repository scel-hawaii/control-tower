#include <Arduino.h>
#include <Adafruit_BMP085.h>

#ifndef GD_DEV_BMP085_H
#define GD_DEV_BMP085_H
void gd_dev_bmp085_open(void);
int gd_dev_bmp085_avail(void);
uint32_t gd_dev_bmp085_read(void);
int16_t gd_dev_bmp085_read_temp(void);
#endif
