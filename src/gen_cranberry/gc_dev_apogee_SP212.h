/*******************************
 *
 * File: gc_dev_apogee_sp215.h
 *
 * Contains prototypes for solar irradiance functions
 *
 ******************************/

#include <Adafruit_ADS1015.h>
#include <Wire.h>

#ifndef GC_DEV_SOLAR_H
#define GC_DEV_SOLAR_H
void gc_dev_apogee_SP212_open(void);
uint16_t gc_dev_apogee_SP212_solar_irr_read(void);
void gc_dev_apogee_SP212_solar_irr_test(void);
#endif
