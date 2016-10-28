#include <Arduino.h>

#define _PIN_GD_BATT_ A0

#ifndef GD_DEV_BATT_H
#define GD_DEV_BATT_H
void gd_dev_batt_open(void);
int gd_dev_batt_read(void);
#endif
