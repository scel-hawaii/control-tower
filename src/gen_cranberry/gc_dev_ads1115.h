#include <Adafruit_ADS1015.h>

#ifndef GC_DEV_SOLAR_H
#define GC_DEV_SOLAR_H
void gc_dev_solar_open(void);
uint16_t gc_dev_solar_read(void);
#endif
