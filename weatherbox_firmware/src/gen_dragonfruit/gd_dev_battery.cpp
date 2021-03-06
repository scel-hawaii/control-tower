/*******************************
 *
 * File: gd_dev_battery.cpp
 *
 * This module is a driver for checking the battery reading in mV.
 *
 ******************************/

#include "gd_dev_battery.h"

/******************************
 *
 * Name:        gd_dev_battery_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize battery reading pins
 *
 ******************************/
void gd_dev_battery_open(void){
    pinMode(_PIN_GD_BATT_, INPUT);
}

/******************************
 *
 * Name:        gd_dev_battery_read
 * Returns:     Battery reading in mV
 * Parameter:   Nothing
 * Description: Reads battery voltage
 *
 ******************************/
int gd_dev_battery_read(void){
    int value = 555;

    #ifndef SEN_STUB
    // Function returns the battery reading as an integer in the range from 0 to 1023.
    // Divide by 1023 to offset and then convert to mV.
    value = analogRead(_PIN_GD_BATT_)*5000.0/1023;
    #endif

    return value;
}

/******************************
 *
 * Name:        gd_dev_battery_test
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Used by the POST function to sample the
 *              sensor and displays the sample to the Serial Monitor
 *
 ******************************/

void gd_dev_battery_test(void){
    Serial.println(F("[P] Check battery value"));
    uint16_t battery_val = gd_dev_battery_read();

    Serial.print(F("[P] battery value: "));
    Serial.print(battery_val);
    Serial.println(F(" mV"));

    if(battery_val < 0){
        Serial.println(F("[P] \tError: battery value out of range"));
    }
}
