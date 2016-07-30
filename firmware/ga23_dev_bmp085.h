#include <Arduino.h>
#include <Adafruit_BMP085.h>

#ifndef GA23_DEV_BMP085_H
#define GA23_DEV_BMP085_H
void ga23_dev_bmp085_open(void);
int ga23_dev_bmp085_avail(void);
int ga23_dev_bmp085_read(void);
float ga23_dev_bmp085_read_temp(void);
#endif

