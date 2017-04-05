/*******************************
 *
 * File: gg_dev_adafruit_BME280_humidity.cpp
 *
 * This module is a driver for the BME280 sensor that
 * will measure humidity. This is not technically an Adafruit
 * sensor, Adafruit just produces the breakout board. The sensor
 * is produced by Bosch Sensortec
 *
 * Product Page: https://www.adafruit.com/product/2652
 * Datasheet: https://cdn-shop.adafruit.com/datasheets/BST-BME280_DS001-10.pdf
 *
 ******************************/

#include "gg_dev_adafruit_BME280_humidity.h"


#define I2C //Define communication protocol as seen below

#ifdef I2C
Adafruit_BME280 bme_humidity; // I2C
#endif

#ifdef HardwareSPI
Adafruit_BME280 bme_humidity(BME_CS); // Hardware SPI
#endif

#ifdef SoftwareSPI
Adafruit_BME280 bme_humidity(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // Software SPI
#endif

void gg_dev_adafruit_BME280_humidity_open(void) {
  bme_humidity.begin();
}

uint16_t gg_dev_adafruit_BME280_humidity_read(void) {
  int value = 50;

  #ifndef SEN_STUB
  value = bme_humidity.readHumidity();
  #endif

  return value;
}
