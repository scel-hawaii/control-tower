/*******************************
 *
 * File: ga_dev_apogee_SP212_irradiance.cpp
 *
 * This module is a driver for the solar irradiance sensor. It uses the
 * Apogee sp215 analog sensor to measure solar irradiance in millivolts (mV) and the ADS1100
 * ADC converter to convert the Apogee sp215 reading into a digital value.
 *
 * Product page: http://www.apogeeinstruments.com/sp-215-amplified-0-5-volt-pyranometer/
 * Datasheet: http://www.apogeeinstruments.com/content/SP-100-200-spec-sheet.pdf
 *
 * Product page: http://www.ti.com/product/ADS1100
 * Datasheet: http://www.ti.com/lit/ds/symlink/ads1100.pdf
 *
 * ****************************/

#include "ga_dev_apogee_SP212_irradiance.h"

/******************************
 *
 * Name:        ga_dev_apogee_SP212_irradiance_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize solar irradiance sensor
 *
 ******************************/

void ga_dev_apogee_SP212_irradiance_open(void){
    pinMode(_PIN_GA_APOGEE_SP212_IRRADIANCE_, INPUT);
}

/******************************
 *
 * Name:        ga_dev_apogee_SP212_irradiance_read_raw
 * Returns:     Solar irradiance value in millivolts (mV)
 * Parameter:   Nothing
 * Description: Reads solar irradiance sensor without conversion
 *
 ******************************/

int ga_dev_apogee_SP212_irradiance_read_raw(void){
    int value = analogRead(_PIN_GA_APOGEE_SP212_IRRADIANCE_);
    return value;
}

/******************************
 *
 * Name:        ga_dev_apogee_sp212_read
 * Returns:     Solar irradiance value in millivolts (mV)
 * Parameter:   Nothing
 * Description: Reads solar irradiance sensor with conversion
 *
 ******************************/

int ga_dev_apogee_SP212_irradiance_read(void){
    int value = 555;
    #ifndef SEN_STUB
    value = (float)analogRead(_PIN_GA_APOGEE_SP212_IRRADIANCE_)*(5000.0/1023.0);
    #endif
    return value;
}
