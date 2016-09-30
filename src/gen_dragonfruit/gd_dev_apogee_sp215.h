#include <Arduino.h>
#include <Wire.h>

#define _PIN_GD_APOGEE_SP215_ 0x48

#ifndef GD_DEV_APOGEE_SP215_H
#define GD_DEV_APOGEE_SP215_H
void gd_dev_apogee_sp215_open(void);
int gd_dev_apogee_sp215_read(void);
#endif
