/*******************************
 *
 * File: gg_dev_bmp085.cpp
 *
 * This module is a driver for the pressure and
 * temperature sensor.
 *
 * Product Page:
 * Datasheet:
 *
 ******************************/

#include "gg_dev_bmp085.h"
static Adafruit_BMP085 bmp085;

/******************************
 *
 * Name:        gg_dev_bmp085_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize bmp085 sensor
 *
 ******************************/

void gg_dev_bmp085_open(void){
    bmp085.begin();
}

/******************************
 *
 * Name:        gg_dev_bmp085_read_press
 * Returns:     Pressure in Pascals (Pa)
 * Parameter:   Nothing
 * Description: Read the pressure from the bmp085 sensor
 *
 ******************************/

uint32_t gg_dev_bmp085_read_press(void){
    uint32_t value = 100000;

    #ifndef SEN_STUB
    value = bmp085.readPressure();
    #endif

    return value;
}

/******************************
 *
 * Name:        gg_dev_bmp085_read_temp
 * Returns:     Temperature in Celsius (C)
 * Parameter:   Nothing
 * Description: Read the temperature from the bmp085 sensor
 *
 ******************************/

int16_t gg_dev_bmp085_read_temp(void){
    int16_t value = 1000;

    #ifndef SEN_STUB
    float value_f = bmp085.readTemperature();
    value = value_f * 10;
    #endif

    return value;
}
