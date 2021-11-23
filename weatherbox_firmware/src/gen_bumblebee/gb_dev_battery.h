/*******************************
 *
 * File: gb_dev_battery.h
 *
 * Contains prototypes for battery reading functions
 *
 ******************************/

#include <Arduino.h>

#define _PIN_GB_BATTERY_ A2

#ifndef GB_DEV_BATTERY_H
#define GB_DEV_BATTERY_H
void gb_dev_battery_open(void);
int gb_dev_battery_read_raw(void);
int gb_dev_battery_read(void);
#endif
