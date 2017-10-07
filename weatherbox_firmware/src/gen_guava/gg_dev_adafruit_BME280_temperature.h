/*******************************
 *
 * File: gg_dev_adafruit_BME280_temperature.h
 *
 * Contains prototypes to get temperature from BME280
 *
 ******************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#ifndef GG_DEV_ADAFRUIT_BME280_TEMPERATURE_H
#define GG_DEV_ADAFRUIT_BME280_TEMPERATURE_H
void gg_dev_adafruit_BME280_temperature_open(void);
uint16_t gg_dev_adafruit_BME280_temperature_read(void);
#endif
