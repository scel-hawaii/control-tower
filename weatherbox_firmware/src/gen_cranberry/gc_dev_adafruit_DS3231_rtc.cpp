/*******************************
 *
 * File: gc_dev_adafruit_DS3231_rtc.cpp
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

#include "gc_dev_adafruit_DS3231_rtc.h"
#include "Adafruit_DS3231.h"

static RTC_DS3231 rtc;
DateTime now = rtc.now();

/******************************
 *
 * Name:        gc_dev_adafruit_DS3231_rtc_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize rtc sensor
 *
 ******************************/

void gc_dev_adafruit_DS3231_rtc_open(void){
    rtc.begin();
}

/******************************
 *
 * Name:        gc_dev_adafruit_DS3231_rtc_yr_read
 * Returns:     rtc value in Pa
 * Parameter:   Nothing
 * Description: Reads rtc sensor
 *
 ******************************/

uint16_t gc_dev_adafruit_DS3231_rtc_year_read(void){
    uint16_t value = 0;

    #ifndef SEN_STUB
    value = now.year();
    #endif

    return value;
}
/******************************
 *
 * Name:        gc_dev_adafruit_DS3231_rtc_mon_read
 * Returns:     rtc value in Pa
 * Parameter:   Nothing
 * Description: Reads rtc sensor
 *
 ******************************/

uint8_t gc_dev_adafruit_DS3231_rtc_month_read(void){
    uint8_t value = 0;

    #ifndef SEN_STUB
    value = now.month();
    #endif

    return value;
}
/******************************
 *
 * Name:        gc_dev_adafruit_DS3231_rtc_mon_read
 * Returns:     rtc value in Pa
 * Parameter:   Nothing
 * Description: Reads rtc sensor
 *
 ******************************/

uint8_t gc_dev_adafruit_DS3231_rtc_day_read(void){
    uint8_t value = 0;

    #ifndef SEN_STUB
    value = now.day();
    #endif

    return value;
}

/******************************
 *
 * Name:        gc_dev_adafruit_DS3231_rtc_mon_read
 * Returns:     rtc value in Pa
 * Parameter:   Nothing
 * Description: Reads rtc sensor
 *
 ******************************/

uint8_t gc_dev_adafruit_DS3231_rtc_hour_read(void){
    uint8_t value = 0;

    #ifndef SEN_STUB
    value = now.hour();
    #endif

    return value;
}
/******************************
 *
 * Name:        gc_dev_adafruit_DS3231_rtc_mon_read
 * Returns:     rtc value in Pa
 * Parameter:   Nothing
 * Description: Reads rtc sensor
 *
 ******************************/

uint8_t gc_dev_adafruit_DS3231_rtc_min_read(void){
    uint8_t value = 0;

    #ifndef SEN_STUB
    value = now.minute();
    #endif

    return value;
}
/******************************
 *
 * Name:        gc_dev_adafruit_DS3231_rtc_mon_read
 * Returns:     rtc value in Pa
 * Parameter:   Nothing
 * Description: Reads rtc sensor
 *
 ******************************/

uint8_t gc_dev_adafruit_DS3231_rtc_sec_read(void){
    uint8_t value = 0;

    #ifndef SEN_STUB
    value = now.second();
    #endif

    return value;
}
/******************************
 *
 * Name:        gc_dev_adafruit_MPL115A2_rtc_pa_test
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Used by the POST function to sample the
 *              sensor and displays the sample to Serial Monitor
 *
 ******************************/

void gc_dev_adafruit_DS3231_rtc_test(void){

    Serial.print(gc_dev_adafruit_DS3231_rtc_year_read(), DEC);
    Serial.print('/');
    Serial.print(gc_dev_adafruit_DS3231_rtc_month_read(), DEC);
    Serial.print('/');
    Serial.print(gc_dev_adafruit_DS3231_rtc_day_read(), DEC);
    Serial.print(" (");
    Serial.print(gc_dev_adafruit_DS3231_rtc_hour_read(), DEC);
    Serial.print(':');
    Serial.print(gc_dev_adafruit_DS3231_rtc_min_read(), DEC);
    Serial.print(':');
    Serial.print(gc_dev_adafruit_DS3231_rtc_sec_read(), DEC);
    Serial.println();

}
