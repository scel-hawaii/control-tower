/*******************************
 *
 * File: ga_dev_adafruit_DS3231_rtc.cpp
 *
 * This module is a driver for the ds3231 rtc sensor
 * that measures rtc in Pa. Technically this is not an
 * Adafruit sensor - Adafruit creates the breakout board for
 * this sensor that is actually manufactured by Freescale.
 *
 * Product page:
 * Datasheet:
 *
 ******************************/

#include "ga_dev_adafruit_DS3231_rtc.h"
#include "Adafruit_DS3231.h"

static RTC_DS3231 rtc;
DateTime now;

/******************************
 *
 * Name:        ga_dev_adafruit_DS3231_rtc_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize rtc sensor
 *
 ******************************/

void ga_dev_adafruit_DS3231_rtc_open(void){
    rtc.begin();
    now = rtc.now();
}

/******************************
 *
 * Name:        ga_dev_adafruit_DS3231_rtc_time_read
 * Returns:     rtc value in MMDDYY
 * Parameter:   Nothing
 * Description: Reads rtc sensor
 *
 ******************************/

uint16_t ga_dev_adafruit_DS3231_rtc_date_read(void){
    uint16_t date = 0;

    date = now.month() * 10000;
    date = date + (now.day() * 1000);
    date = date + now.year();

    return date;
}

/******************************
 *
 * Name:        ga_dev_adafruit_DS3231_rtc_mon_read
 * Returns:     rtc value in HHMMSS
 * Parameter:   Nothing
 * Description: Reads rtc sensor
 *
 ******************************/

uint16_t ga_dev_adafruit_DS3231_rtc_time_read(void){
    uint16_t time = 0;

    time = now.hour() * 10000;
    time = time + (now.minute() * 1000);
    time = time + now.second();

    return time;
}
