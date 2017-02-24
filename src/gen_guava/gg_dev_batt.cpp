/*******************************
 *
 * File: gg_dev_batt.cpp
 *
 * This module is a driver for checking the battery reading in mV.
 *
 ******************************/

#include "gg_dev_batt.h"

/******************************
 *
 * Name:        gg_dev_batt_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize battery reading pins
 *
 ******************************/

void gg_dev_batt_open(void){
    pinMode(_PIN_gg_BATT_, INPUT);
}

/******************************
 *
 * Name:        gg_dev_batt_read_raw
 * Returns:     Battery reading in mV
 * Parameter:   Nothing
 * Description: Reads battery voltage without conversion
 *
 ******************************/

int gg_dev_batt_read_raw(void){
    int value;
    value = analogRead(_PIN_gg_BATT_);
    return value;
}

/******************************
 *
 * Name:        gg_dev_batt_read
 * Returns:     Battery reading in mV
 * Parameter:   Nothing
 * Description: Reads battery voltage with conversion
 *
 ******************************/

int gg_dev_batt_read(void){
    int val = 555;

    #ifndef SEN_STUB
    float raw = (float)analogRead(_PIN_gg_BATT_) * (5.0/1023.0);
    val = raw * 1000;
    #endif

    return val;
}
