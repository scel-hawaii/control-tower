/*******************************
 *
 * File: gg_dev_solar_panel.cpp
 *
 * This module is a driver for the solar panel module. It uses the
 * Adafruit "Huge 6V 6W Solar panel" to measure panel voltage in mV.
 *
 * Product page: https://www.adafruit.com/products/1525
 *
 ******************************/

#include "gg_dev_solar_panel.h"

/******************************
 *
 * Name:        gg_dev_solar_panel_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize solar panel pins
 *
 ******************************/

void gg_dev_solar_panel_open(void){
    pinMode(_PIN_GG_SOLAR_PANEL_, INPUT);
}
/******************************
 *
 * Name:        gg_dev_solar_panel_read_raw
 * Returns:     Solar Panel reading in mV
 * Parameter:   Nothing
 * Description: Reads solar panel voltage without conversion
 *
 ******************************/

int gg_dev_solar_panel_read_raw(void){
    int value;
    value = analogRead(_PIN_GG_SOLAR_PANEL_);
    return value;
}
/******************************
 *
 * Name:        gg_dev_solar_panel_read
 * Returns:     Solar panel voltage in mV
 * Parameter:   Nothing
 * Description: Read solar panel voltage
 *
 ******************************/

int gg_dev_solar_panel_read(void){
    int value = 555;

    #ifndef SEN_STUB
    value = 3.0*(float)analogRead(_PIN_GG_SOLAR_PANEL_)*(3300.0/1023.0);
    #endif

    return value;
}
