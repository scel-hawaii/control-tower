#include <Arduino.h>
#include <SHT1x.h>

#ifndef GC_DEV_SHT1X_H
#define GC_DEV_SHT1X_H
void gc_dev_sht1x_open(void);
int gc_dev_sht1x_avail(void);
int gc_dev_sht1x_read(void);
#endif
