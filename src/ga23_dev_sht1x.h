#include <Arduino.h>
#include <SHT1x.h>

#ifndef GA23_DEV_SHT1X_H
#define GA23_DEV_SHT1X_H
void ga23_dev_sht1x_open(void);
int ga23_dev_sht1x_avail(void);
int ga23_dev_sht1x_read(void);
#endif

