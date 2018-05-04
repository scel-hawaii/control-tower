/*******************************
 *
 * File: gg_dev_battery.cpp
 *
 * This module is a driver for checking the battery reading in mV.
 *
 ******************************/

#include "gg_dev_battery.h"

/******************************
 *
 * Name:        gg_dev_battery_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize battery reading pins
 *
 ******************************/

void gg_dev_battery_open(void){

}

/******************************
 *
 * Name:        gg_dev_battery_read
 * Returns:     Battery reading in mV
 * Parameter:   Nothing
 * Description: Reads battery voltage with conversion
 *
 ******************************/

uint16_t gg_dev_battery_read(void){
    uint16_t val = 555;

    #ifndef SEN_STUB
    float raw = (float)analogRead(_PIN_GG_BATTERY_) * (3.8/1023.0);
    val = raw * 1000;
    #endif

    return val;
}
