/*******************************
 *
 * File: ga_dev_DS3231_rtc.cpp
 *
 * This module is a driver for the real-time clock(RTC) DS3231 sensor
 * that will grab the current unix time.
 *
 * Product page: https://learn.adafruit.com/adafruit-ds3231-precision-rtc-breakout
 *
 ******************************/
#include "ga_dev_DS3231_rtc.h"
#include "RTClib.h"

RTC_Millis rtc; //using just software based on millis() & timer

/******************************
 *
 * Name:        ga_dev_DS3231_rtc_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize rtc sensor with time of compiler
 *
 ******************************/
void ga_dev_DS3231_rtc_open(void){
    rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
}

/******************************
 *
 * Name:        ga_dev_DS3231_rtc_unix_read
 * Returns:     rtc value in unix time
 * Parameter:   Nothing
 * Description: Reads rtc sensor
 *
 ******************************/
uint32_t ga_dev_DS3231_rtc_unix_read(void){
  DateTime now = rtc.now();
  uint32_t value;
  #ifndef SEN_STUB
  value = now.unixtime();
  #endif
  return value;
}
