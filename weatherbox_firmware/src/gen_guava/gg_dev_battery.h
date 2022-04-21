/*******************************
 *
 * File: gg_dev_battery.h
 *
 * Contains prototypes for battery reading functions
 *
 ******************************/

#include <Arduino.h>

#define _PIN_GG_BATTERY_ A1

#ifndef GG_DEV_BATTERY_H
#define GG_DEV_BATTERY_H
void gg_dev_battery_open(void);
int gg_dev_battery_read_raw(void);
int gg_dev_battery_read(void);
#endif
