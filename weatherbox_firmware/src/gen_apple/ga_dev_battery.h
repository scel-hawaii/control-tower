/*******************************
 *
 * File: ga_dev_battery.h
 *
 * Contains prototypes for battery reading functions
 *
 ******************************/

#include <Arduino.h>

#define _PIN_GA_BATTERY_ A3

#ifndef GA_DEV_BATTERY_H
#define GA_DEV_BATTERY_H
void ga_dev_battery_open(void);
int ga_dev_battery_read_raw(void);
int ga_dev_battery_read(void);
#endif
