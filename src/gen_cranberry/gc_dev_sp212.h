#include <Adafruit_ADS1015.h>
#include <Wire.h>

#ifndef GC_DEV_SOLAR_H
#define GC_DEV_SOLAR_H
void gc_dev_sp212_open(void);
uint16_t gc_dev_sp212_read(void);
#endif
