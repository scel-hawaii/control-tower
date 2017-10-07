/*******************************
 *
 * File: gc_dev_battery.h
 *
 * Contains prototypes for battery reading functions
 *
 ******************************/

#include <Adafruit_ADS1015.h>
#include <Wire.h>

#ifndef GC_DEV_BATT_H
#define GC_DEV_BATT_H
void gc_dev_battery_open(void);
uint16_t gc_dev_battery_read(void);
void gc_dev_battery_test(void);
#endif
