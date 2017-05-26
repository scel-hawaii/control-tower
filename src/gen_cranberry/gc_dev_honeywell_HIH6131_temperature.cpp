/*******************************
 *
 * File: gc_dev_honeywell_HIH6131_temperature.cpp
 *
 * This module is a driver for the temperature sensor. It uses the Honeywell
 * HIH6131 sensor to measure the temperature value.
 *
 * Product page: https://sensing.honeywell.com/HIH6131-021-001-humidity-sensors
 * Datasheet: https://sensing.honeywell.com/honeywell-sensing-humidicon-hih6100-series-product-sheet-009059-6-en.pdf
 *
 ******************************/

#include "gc_dev_honeywell_HIH6131_temperature.h"
#include "HIH613x.h"

static HIH613x hih6131(0x27);

/******************************
 *
 * Name:        gc_dev_honeywell_HIH6131_temperature_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize humidity sensor
 *
 ******************************/

void gc_dev_honeywell_HIH6131_temperature_open(void){
    Wire.begin(9600);
}

/******************************
 *
 * Name:        gc_dev_honeywell_HIH6131_temperature_centik_read
 * Returns:     Temperature in centi-Kelvin
 * Parameter:   Nothing
 * Description: Read temperature sensor
 *
 ******************************/

uint16_t gc_dev_honeywell_HIH6131_temperature_centik_read(void){
    int16_t value = 30000;

    #ifndef SEN_STUB
    hih6131.update();
    //value = (float)hih6131.getTemperature()*100.0 + 27315.0;
    value = (float)hih6131.getTemperature();
    #endif

    return value;
}

/******************************
 *
 * Name:        gc_dev_honeywell_HIH6131_temperature_centik_test
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Used by the POST function to sample the
 *              sensor and displays the sample to the Serial Monitor
 *
 ******************************/

void gc_dev_honeywell_HIH6131_temperature_centik_test(void){
    Serial.println(F("[P] Check hih6131_temperature_centik value"));
    int hih6131_temperature_centik_val = gc_dev_honeywell_HIH6131_temperature_centik_read();

    Serial.print(F("[P] hih6131_temperature_centik value: "));
    Serial.print(hih6131_temperature_centik_val);
    Serial.println(F(" cK"));

    if(hih6131_temperature_centik_val < 0){
        Serial.println(F("[P] \tError: hih6131 temp out of range"));
    }
}
