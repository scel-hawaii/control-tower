/*******************************
 *
 * File: gb_dev_adafruit_BME280_sensor.cpp
 *
 * This module is a driver for the BME280 sensor that
 * will measure humidity, temperature, and pressure.
 * This is not technically an Adafruit sensor,
 * Adafruit just produces the breakout board. The sensor
 * is produced by Bosch Sensortec
 *
 * Product Page: https://www.adafruit.com/product/2652
 * Datasheet: https://cdn-shop.adafruit.com/datasheets/BST-BME280_DS001-10.pdf
 *
 ******************************/

#include "gb_dev_adafruit_BME280_sensor.h"


#define I2C //Define communication protocol as seen below

#ifdef I2C
Adafruit_BME280 bme280; // I2C
#endif

#ifdef HardwareSPI
Adafruit_BME280 bme280(BME_CS); // Hardware SPI
#endif

#ifdef SoftwareSPI
Adafruit_BME280 bme280(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // Software SPI
#endif

void gb_dev_adafruit_BME280_sensor_open(void) {
  bme280.begin();
}

uint16_t gb_dev_adafruit_BME280_humidity_read(void) {
  uint16_t value = 50;

  #ifndef SEN_STUB
  value = bme280.readHumidity();
  #endif

  return value;
}

uint32_t gb_dev_adafruit_BME280_pressure_read(void) {
  uint32_t value = 10000;

  #ifndef SEN_STUB
  value = bme280.readPressure();
  #endif

  return value;
}

uint16_t gb_dev_adafruit_BME280_temperature_read(void) {
  uint16_t value = 100;

  #ifndef SEN_STUB
  value = bme280.readTemperature() + 273;
  #endif

  return value;
}
