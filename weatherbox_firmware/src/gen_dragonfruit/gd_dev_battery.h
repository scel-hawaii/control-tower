/*******************************
 *
 * File: gd_dev_battery.h
 *
 * Contains prototypes for battery reading functions
 *
 ******************************/

#include <Arduino.h>

#define _PIN_GD_BATT_ A7

#ifndef GD_DEV_BATTERY_H
#define GD_DEV_BATTERY_H
void gd_dev_battery_open(void);
int gd_dev_battery_read(void);
void gd_dev_battery_test(void);
#endif
