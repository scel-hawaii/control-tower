/*******************************
 *
 * File: gd_dev_apogee_SP215_irradiance.h
 *
 * Contains prototypes for solar irradiance functions
 *
 ******************************/

#include <Arduino.h>
#include <Wire.h>

#define _DEV_ADDR_GD_ADS1100_ 0x48

#ifndef GD_DEV_APOGEE_SP215_IRRADIANCE_H
#define GD_DEV_APOGEE_SP215_IRRADIANCE_H
void gd_dev_apogee_SP215_irradiance_open(void);
uint32_t gd_dev_apogee_SP215_irradiance_read(void);
void gd_dev_apogee_SP215_irradiance_test(void);
#endif
