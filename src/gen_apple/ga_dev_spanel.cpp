/*******************************
 *
 * File: ga_dev_spanel.cpp
 *
 * This module is a driver for the solar panel module. It uses the
 * Adafruit "Huge 6V 6W Solar panel" to measure panel voltage in mV.
 *
 * Product page: https://www.adafruit.com/products/1525
 *
 ******************************/

#include "ga_dev_spanel.h"

/******************************
 *
 * Name:        ga_dev_spanel_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize solar panel pins
 *
 ******************************/

void ga_dev_spanel_open(void){
    pinMode(_PIN_GA_SPANEL_, INPUT);
}

/******************************
 *
 * Name:        ga_dev_spanel_read
 * Returns:     Solar panel voltage in mV
 * Parameter:   Nothing
 * Description: Read solar panel voltage
 *
 ******************************/

int ga_dev_spanel_read(void){
    int value = 555;

    #ifndef SEN_STUB
    value = 2.0*(float)analogRead(_PIN_GA_SPANEL_)*(5000.0/1023.0)+(70.0);
    #endif

    return value;
}
