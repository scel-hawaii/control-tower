/*******************************
 *
 * File: ga_dev_DS3231_rtc.h
 *
 * Contains prototypes for rtc sensor functions
 *
 ******************************/
 #include <Arduino.h>
 #include <Wire.h>  // this #include still required because the RTClib depends on it
 #include "RTClib.h"

#ifndef GA_DEV_DS3231_H
#define GA_DEV_DS3231_H

void ga_dev_DS3231_rtc_open(void);
uint32_t ga_dev_DS3231_rtc_unix_read(void);
#endif
