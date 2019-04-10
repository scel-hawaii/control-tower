/*******************************
 *
 * File: gc_dev_adafruit_DS3231_rtc.h
 *
 * Contains prototypes for rtc sensor functions
 *
 ******************************/

#include <Wire.h>
#include "Adafruit_DS3231.h"

#ifndef GC_DEV_DS3231_H
#define GC_DEV_DS3231_H

void gc_dev_adafruit_DS3231_rtc_open(void);
uint16_t gc_dev_adafruit_DS3231_rtc_date_read(void);
uint16_t gc_dev_adafruit_DS3231_rtc_time_read(void);
void gc_dev_adafruit_DS3231_rtc_test(void);
#endif
