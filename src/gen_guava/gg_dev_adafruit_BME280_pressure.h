/*******************************
 *
 * File: gg_dev_adafruit_BME280_pressure.h
 *
 * Contains prototypes to get pressure from BME280
 *
 ******************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#ifndef GG_DEV_ADAFRUIT_BME280_PRESSURE_H
#define GG_DEV_ADAFRUIT_BME280_PRESSURE_H
void gg_dev_adafruit_BME280_pressure_open(void);
uint16_t gg_dev_adafruit_BME280_pressure_read(void);
#endif
