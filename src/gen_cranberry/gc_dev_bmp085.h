#include <Arduino.h>
#include <Adafruit_BMP085.h>

#ifndef GC_DEV_BMP085_H
#define GC_DEV_BMP085_H
void gc_dev_bmp085_open(void);
int gc_dev_bmp085_avail(void);
uint32_t gc_dev_bmp085_read(void);
uint16_t gc_dev_bmp085_read_temp(void);
#endif
