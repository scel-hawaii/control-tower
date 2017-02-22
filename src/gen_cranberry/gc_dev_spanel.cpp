/*******************************
 *
 * File: gc_dev_spanel.cpp
 *
 * This module is a driver for the solar panel module. It uses the
 * Adafruit "Huge 6V 6W Solar panel" to measure panel voltage in mV.
 *
 * Product page: https://www.adafruit.com/products/1525
 *
 ******************************/

#include "gc_dev_spanel.h"

static Adafruit_ADS1115 adc;

/******************************
 *
 * Name:        gc_dev_spanel_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize solar panel pins
 *
 ******************************/

void gc_dev_spanel_open(void){
    adc.begin();
}

/******************************
 *
 * Name:        gc_dev_spanel_read
 * Returns:     Solar panel voltage in mV
 * Parameter:   Nothing
 * Description: Read solar panel voltage
 *
 ******************************/

uint16_t gc_dev_spanel_read(void){
  uint16_t value = 6000;

  #ifndef SEN_STUB
  value = ((float)adc.readADC_SingleEnded(3)*188.0)/(1000.0);
  #endif

  return value;
}

/******************************
 *
 * Name:        gc_dev_spanel_test
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Used by the POST function to sample the
 *              sensor and displays the sample to the Serial Monitor
 *
 ******************************/

void gc_dev_spanel_test(void){
    Serial.println(F("[P] check panel sensor value"));

    uint16_t spanel_val = gc_dev_spanel_read();
    Serial.print(F("[P] spanel value: "));
    Serial.print(spanel_val);
    Serial.println(F(" mV"));

    if(spanel_val < 100){
        Serial.println(F("[P] \tERROR: spanel value out of range"));
    }
}
