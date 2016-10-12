#include <Adafruit_ADS1015.h>
#include <Wire.h>

#ifndef GC_DEV_SPANEL
#define GC_DEV_SPANEL
void gc_dev_spanel_open(void);
int gc_dev_spanel_read(void);
#endif
