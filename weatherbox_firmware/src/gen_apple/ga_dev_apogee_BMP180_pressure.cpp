/*******************************
 *
 * File: ga_dev_apogee_BM180_pressure.cpp
 *
 * This module is a driver for the pressure and
 * temperature sensor.
 *
 * Product Page: https://www.adafruit.com/product/1603
 * Datasheet: https://cdn-shop.adafruit.com/datasheets/BST-BMP180-DS000-09.pdf
 *
 ******************************/

#include "ga_dev_apogee_BMP180_pressure.h"
static Adafruit_BMP085 bmp180;

/******************************
 *
 * Name:        ga_dev_apogee_BM180_pressure_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize BMP180 sensor
 *
 ******************************/

void ga_dev_apogee_BMP180_pressure_open(void){
    bmp180.begin();
}

/******************************
 *
 * Name:        ga_dev_apogee_BMP180_pressure_read
 * Returns:     Pressure in Pascals (Pa)
 * Parameter:   Nothing
 * Description: Read the pressure from the BMP180 sensor
 *
 ******************************/

uint32_t ga_dev_apogee_BMP180_pressure_read(void){
    uint32_t value = 100000;

    #ifndef SEN_STUB
    value = bmp180.readPressure();
    #endif

    return value;
}
