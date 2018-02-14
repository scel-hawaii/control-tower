/*******************************
 *
 * File: gd_dev_adafruit_MPL115A2_temperature.cpp
 *
 * This module is a driver for the temperature sensor. It uses the
 * Adafruit MPL115A2 sensor to measure temperature in cK. Technically
 * this is not an Adafruit sensor - Adafruit creates the breakout
 * board for this sensor that is actually manufactured by Freescale.
 *
 * Product page: http://www.nxp.com/products/sensors/pressure-sensors/barometric-pressure-15-to-115-kpa/50-to-115kpa-absolute-digital-pressure-sensor:MPL115A
 * Datasheet: http://www.nxp.com/assets/documents/data/en/data-sheets/MPL115A2.pdf
 *
 ******************************/

#include "gd_dev_adafruit_MPL115A2_temperature.h"
#include "Adafruit_MPL115A2.h"

static Adafruit_MPL115A2 mpl115a2t1;

/******************************
 *
 * Name:        gd_dev_adafruit_MPL115A2_temperature_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize temperature sensor
 *
 ******************************/

void gd_dev_adafruit_MPL115A2_temperature_open(void){
    mpl115a2t1.begin();
}

/******************************
 *
 * Name:        gd_dev_adafruit_MPL115A2_temperature_read
 * Returns:     Temperature value in centiKelvin (cK)
 * Parameter:   Nothing
 * Description: Reads temperature sensor
 *
 ******************************/

uint16_t gd_dev_adafruit_MPL115A2_temperature_centik_read(void){
  uint16_t value = 0;
  float raw_value;
  #ifndef SEN_STUB
  raw_value = mpl115a2t1.getTemperature(); //Function returns floating point value in Celcius
  value = ((raw_value + 273.15) * 100); //Convert to centiKelvin (cK)
  #endif
  return (uint16_t)value;
}

/******************************
 *
 * Name:        gd_dev_adafruit_MPL115A2_temperature_centik_test
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Used by the POST function to sample the
 *              sensor and displays the sample to Serial Monitor
 *
 ******************************/

void gd_dev_adafruit_MPL115A2_temperature_centik_test(void) {
  Serial.println(F("[P] Check mpl115a2t1_temperature_centik value"));
  uint32_t mpl115a2t1_temperature_centik_val = gd_dev_adafruit_MPL115A2_temperature_centik_read();

  Serial.print(F("[P] mpl115a2t1_temperature_centik value: "));
  Serial.print(mpl115a2t1_temperature_centik_val);
  Serial.println(F(" cK"));

  if(mpl115a2t1_temperature_centik_val < 0){
      Serial.println(F("[P] \tError: mpl115a2t1 temperature out of range"));
  }
}
