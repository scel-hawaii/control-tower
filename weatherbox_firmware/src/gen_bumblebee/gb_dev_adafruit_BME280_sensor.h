#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#ifndef GG_DEV_ADAFRUIT_BME280_SENSOR_H
#define GG_DEV_ADAFRUIT_BME280_SENSOR_H

void gb_dev_adafruit_BME280_sensor_open(void);
uint16_t gb_dev_adafruit_BME280_temperature_read(void);
uint32_t gb_dev_adafruit_BME280_pressure_read(void);
uint16_t gb_dev_adafruit_BME280_humidity_read(void);

#endif