/*******************************
 *
 * File: gg_dev_adafruit_BME280_humidity.h
 *
 * Contains prototypes to get humidity from BME280
 *
 ******************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#ifndef GG_DEV_ADAFRUIT_BME280_HUMIDITY_H
#define GG_DEV_ADAFRUIT_BME280_HUMIDITY_H
void gg_dev_adafruit_BME280_humidity_open(void);
uint16_t gg_dev_adafruit_BME280_humidity_read(void);
#endif
