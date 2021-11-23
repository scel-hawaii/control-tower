/*******************************
 *
 * File: gb_dev_solar_panel.cpp
 *
 * This module is a driver for the solar panel module. It uses the
 * Adafruit "Huge 6V 6W Solar panel" to measure panel voltage in mV.
 *
 * Product page: https://www.adafruit.com/products/1525
 *
 ******************************/

#include "gb_dev_solar_panel.h"

/******************************
 *
 * Name:        gb_dev_solar_panel_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize solar panel pins
 *
 ******************************/

void gb_dev_solar_panel_open(void){
    pinMode(_PIN_GB_SOLAR_PANEL_, INPUT);
}

/******************************
 *
 * Name:        gb_dev_solar_panel_read
 * Returns:     Solar panel voltage in mV
 * Parameter:   Nothing
 * Description: Read solar panel voltage
 *
 ******************************/

int gb_dev_solar_panel_read(void){
    int value = 555;

    #ifndef SEN_STUB
    value = 2.0*(float)analogRead(_PIN_GB_SOLAR_PANEL_)*(5000.0/1023.0)+(70.0);
    #endif

    return value;
}
