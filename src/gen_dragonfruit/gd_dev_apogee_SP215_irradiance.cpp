/*******************************
 *
 * File: gd_dev_apogee_SP215_irradiance.cpp
 *
 * This module is a driver for the solar irradiance sensor. It uses the
 * Apogee sp215 analog sensor to measure solar irradiance in millivolts (mV) and the ADS1100
 * ADC converter to convert the Apogee sp215 reading into a digital value.
 *
 * Product page: http://www.apogeeinstruments.com/sp-215-amplified-0-5-volt-pyranometer/
 * Datasheet: http://www.apogeeinstruments.com/content/SP-100-200-spec-sheet.pdf
 *
 * Product page: http://www.ti.com/product/ADS1100
 * Datasheet: http://www.ti.com/lit/ds/symlink/ads1100.pdf
 *
 * ****************************/

#include "gd_dev_apogee_SP215_irradiance.h"

/******************************
 *
 * Name:        gd_dev_apogee_SP215_irradiance_open
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Initialize solar irradiance sensor
 *
 ******************************/
void gd_dev_apogee_SP215_irradiance_open(void){

    /* Initiate Wire library and join I2C bus as slave */
    Wire.begin();

    /* Begin transmission to the I2C slave device with the given address */
    Wire.beginTransmission(_DEV_ADDR_GD_ADS1100_);

    /* Send configuration register bits to I2C slave device.
       Bit 7: Set ST/BSY bit to 1 to start conversion.
       Bit 6 and 5: Reserved bits defaulted to 0.
       Bit 4: Set SC bit to 0 to perform continuous conversions.
       Bit 3 and 2: Set DR bits to 0b11 to select 8 samples per second.
       Bit 1 and 0: Set PGA bits to 0b00 to select gain of 1. */
    Wire.write(0x8C);

    Wire.endTransmission();
}

/******************************
 *
 * Name:        gd_dev_apogee_SP215_irradiance_read
 * Returns:     Solar irradiance value in millivolts (mV)
 * Parameter:   Nothing
 * Description: Reads solar irradiance sensor
 *
 ******************************/

uint32_t gd_dev_apogee_SP215_irradiance_read(void){
    uint32_t value = 555;
    #ifndef SEN_STUB

    /* Begin transmission to the I2C slave device with the given address */
    Wire.beginTransmission(_DEV_ADDR_GD_ADS1100_);

    /* Request bytes from I2C slave device */
    Wire.requestFrom(_DEV_ADDR_GD_ADS1100_, 3);
    if(Wire.available())
    {
        value = Wire.read();
        value = value << 8;
        value += Wire.read();
    }
    Wire.endTransmission();

    /* Analog to digital conversion with 16-bit resolution. Multiply by 5V
    reference voltage then divide by 0x7FFF to convert the 16-bit ADC reading
    to voltage. 0x7FFF is the maximum positive value of the reading. */
    value = (value*5000.0)/(0x7FFF);
    #endif
    return value;
}

/******************************
 *
 * Name:        gd_dev_apogee_SP215_irradiance_test
 * Returns:     Nothing
 * Parameter:   Nothing
 * Description: Used by the POST function to sample the
 *              sensor and displays the sample to Serial Monitor
 *
 ******************************/

void gd_dev_apogee_SP215_irradiance_test(void) {
  Serial.println(F("[P] Check apogee_SP215_irradiance value"));
  int apogee_sp215_irradiance_val = gd_dev_apogee_SP215_irradiance_read();

  Serial.print(F("[P] apogee_sp215 irradiance value: "));
  Serial.print(apogee_sp215_irradiance_val);
  Serial.println(F(" mV"));

  if(apogee_sp215_irradiance_val < 0){
      Serial.println(F("[P] \tError: apogee irradiance out of range"));
  }
}
