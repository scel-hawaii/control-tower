/*******************************
 *
 * File: ga_dev_battery.cpp
 *
 * This module is a driver for checking the battery reading in mV.
 *
 ******************************/

#include "ga_dev_battery.h"

/******************************
 *
 * Name:        ga_dev_batt_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize battery reading pins
 *
 ******************************/

void ga_dev_battery_open(void){
    pinMode(_PIN_GA_BATTERY_, INPUT);
}

/******************************
 *
 * Name:        ga_dev_batt_read_raw
 * Returns:     Battery reading in mV
 * Parameter:   Nothing
 * Description: Reads battery voltage without conversion
 *
 ******************************/

int ga_dev_battery_read_raw(void){
    int value;
    value = analogRead(_PIN_GA_BATTERY_);
    return value;
}

/******************************
 *
 * Name:        ga_dev_batt_read
 * Returns:     Battery reading in mV
 * Parameter:   Nothing
 * Description: Reads battery voltage with conversion
 *
 ******************************/

int ga_dev_battery_read(void){
    int val = 555;

    #ifndef SEN_STUB
    float raw = (float)analogRead(_PIN_GA_BATTERY_) * (5.0/1023.0);
    val = raw * 1000;
    #endif

    return val;
}
