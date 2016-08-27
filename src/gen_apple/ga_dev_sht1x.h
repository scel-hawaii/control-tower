#include <Arduino.h>
#include <SHT1x.h>

#ifndef GA_DEV_SHT1X_H
#define GA_DEV_SHT1X_H
void ga_dev_sht1x_open(void);
int ga_dev_sht1x_avail(void);
int ga_dev_sht1x_read(void);
#endif

