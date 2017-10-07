/*******************************
 *
 * File: gc_dev_apogee_SP212_irradiance.cpp
 *
 * This module is a driver for the solar irradiance sensor. It uses the
 * Apogee SP212 analog sensor to measure solar irradiance in millivolts (mV)
 *
 * Product page: http://www.apogeeinstruments.com/sp-212-amplified-0-2-5-volt-pyranometer/
 * Datasheet: http://www.apogeeinstruments.com/content/SP-212-SP-215-manual.pdf
 *
 * ****************************/

#include "gc_dev_apogee_SP212_irradiance.h"

static Adafruit_ADS1115 adc;

/******************************
 *
 * Name:        gc_dev_apogee_SP212_irradiance_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize solar irradiance sensor
 *
 ******************************/

void gc_dev_apogee_SP212_irradiance_open(void){
    adc.begin();
}

/******************************
 *
 * Name:        gc_dev_apogee_SP212_irradiance_read
 * Returns:     Solar irradiance value in millivolts (mV)
 * Parameter:   Nothing
 * Description: Reads solar irradiance sensor
 *
 ******************************/

uint16_t gc_dev_apogee_SP212_irradiance_read(void){
    uint16_t value = 4000;

    #ifndef SEN_STUB
    value = ((float)adc.readADC_SingleEnded(0)*188.0)/(1000.0);
    #endif

    return value;
}

/******************************
 *
 * Name:        gc_dev_apogee_SP212_irradiance_test
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Used by the POST function to sample the
 *              sensor and displays the sample to Serial Monitor
 *
 ******************************/

void gc_dev_apogee_SP212_irradiance_test(void){
    Serial.println(F("[P] Check apogee_SP212_irradiance value"));
    int apogee_sp212_irradiance_val = gc_dev_apogee_SP212_irradiance_read();

    Serial.print(F("[P] apogee_sp212 irradiance value: "));
    Serial.print(apogee_sp212_irradiance_val);
    Serial.println(F(" mV"));

    if(apogee_sp212_irradiance_val < 0){
        Serial.println(F("[P] \tError: apogee irradiane out of range"));
    }
}
