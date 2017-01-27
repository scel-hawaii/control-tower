/*******************************
 *
 * File: gd_dev_honeywell_HIH6131.cpp
 *
 * This module is a driver for the humidity sensor. It uses the Honeywell 
 * HIH6131 sensor to measure the humidity percentage value. 
 * 
 * Product page: https://sensing.honeywell.com/HIH6131-021-001-humidity-sensors
 * Datasheet: https://sensing.honeywell.com/honeywell-sensing-humidicon-hih6100-series-product-sheet-009059-6-en.pdf
 *
 ******************************/

#include "gd_dev_honeywell_HIH6131.h"

static HIH613x hih6131(_PIN_GD_HONEYWELL_HIH6131_);

/******************************
 * 
 * Name:        gd_dev_honeywell_HIH6131_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize humidity sensor 
 * 
 ******************************/
void gd_dev_honeywell_HIH6131_open(void)
{
    Wire.begin(9600);
}

/******************************
 * 
 * Name:        gd_dev_honeywell_HIH6131_read
 * Returns:     Humidity percentage
 * Parameter:   Nothing
 * Description: Read humidity sensor 
 * 
 ******************************/
int gd_dev_honeywell_HIH6131_read(void)
{
    int value = 555;
    #ifndef SEN_STUB
    hih6131.update();
    value = hih6131.getHumidity();
    #endif
    return value;
}
