/*******************************
 *
 * File: gd_dev_adafruit_MPL115A2_pressure.h
 *
 * Contains prototypes for pressure sensor functions
 *
 ******************************/

#include <Arduino.h>

#ifndef gd_DEV_MPL115A2_H
#define gd_DEV_MPL115A2_H
void gd_dev_adafruit_MPL115A2_pressure_open(void);
uint32_t gd_dev_adafruit_MPL115A2_pressure_pa_read(void);
void gd_dev_adafruit_MPL115A2_pressure_pa_test(void);
#endif
