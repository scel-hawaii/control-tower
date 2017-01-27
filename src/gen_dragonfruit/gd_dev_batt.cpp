/*******************************
 *
 * File: gd_dev_batt.cpp 
 *
 * This module is a driver for checking the battery reading in mV.
 *
 ******************************/

#include "gd_dev_batt.h"

/******************************
 * 
 * Name:        gd_dev_batt_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize battery reading pins 
 * 
 ******************************/
void gd_dev_batt_open(void){
    pinMode(_PIN_GD_BATT_, INPUT);
}

/******************************
 * 
 * Name:        gd_dev_batt_read
 * Returns:     Battery reading in mV 
 * Parameter:   Nothing
 * Description: Reads battery voltage 
 * 
 ******************************/
int gd_dev_batt_read(void){
    int value = 555;

    #ifndef SEN_STUB
    // Function returns the battery reading as an integer in the range from 0 to 1023.
    // Divide by 1023 to offset and then convert to mV.
    value = analogRead(_PIN_GD_BATT_)*5000.0/1023;  
    #endif                                         

    return value;
}
