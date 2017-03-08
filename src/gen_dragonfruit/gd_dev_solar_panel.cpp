/*******************************
 *
 * File: gd_dev_solar_panel.cpp
 *
 * This module is a driver for the solar panel module. It uses the
 * Adafruit "Huge 6V 6W Solar panel" to measure panel voltage in mV.
 *
 * Product page: https://www.adafruit.com/products/1525
 *
 ******************************/

#include "gd_dev_solar_panel.h"

/******************************
 *
 * Name:        gd_dev_solar_panel_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize solar panel pins
 *
 ******************************/

void gd_dev_solar_panel_open(void){
    pinMode(_PIN_GD_SOLAR_PANEL_, INPUT);
}

/******************************
 *
 * Name:        gd_dev_solar_panel_read
 * Returns:     Solar panel voltage in mV
 * Parameter:   Nothing
 * Description: Read solar panel voltage
 *
 ******************************/

int gd_dev_solar_panel_read(void){
    float value = 555.0;
    #ifndef SEN_STUB

    /* The solar panel has a maximum output voltage of 6V but the ATmega328P
    microcontroller only allows a maximum input voltage of 5V. To prevent a
    saturated signal reading, A physical voltage divider is implemented on the
    board. To account for this voltage divider, a scaling factor of 2 is used. */
    value = 2.0 * (float)analogRead(_PIN_GD_SOLAR_PANEL_) *(5000.0/1023);
    #endif
    return value;
}

/******************************
 *
 * Name:        gd_dev_solar_panel_test
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Used by the POST function to sample the
 *              sensor and displays the sample to the Serial Monitor
 *
 ******************************/

void gd_dev_solar_panel_test(void){
    Serial.println(F("[P] check solar panel sensor value"));

    uint16_t solar_panel_val = gd_dev_solar_panel_read();
    Serial.print(F("[P] solar panel value: "));
    Serial.print(solar_panel_val);
    Serial.println(F(" mV"));

    if(solar_panel_val < 100){
        Serial.println(F("[P] \tERROR: solar panel value out of range"));
    }
}
