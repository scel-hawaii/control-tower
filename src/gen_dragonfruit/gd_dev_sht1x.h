#include <Arduino.h>
#include <SHT1x.h>

#ifndef GD_DEV_SHT1X_H
#define GD_DEV_SHT1X_H
void gd_dev_sht1x_open(void);
int gd_dev_sht1x_avail(void);
int gd_dev_sht1x_read(void);
#endif
