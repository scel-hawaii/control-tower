/*******************************
 *
 * File: gc_dev_batt.h
 *
 * Contains prototypes for battery reading functions
 *
 ******************************/

#include <Adafruit_ADS1015.h>
#include <Wire.h>

#ifndef GC_DEV_BATT_H
#define GC_DEV_BATT_H
void gc_dev_batt_open(void);
uint16_t gc_dev_batt_read(void);
void gc_dev_batt_test(void);
#endif
