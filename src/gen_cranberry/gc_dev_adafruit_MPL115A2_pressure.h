/*******************************
 *
 * File: gc_dev_adafruit_MPL115A2_pressure.h
 *
 * Contains prototypes for pressure sensor functions
 *
 ******************************/

#include <Arduino.h>

#ifndef GC_DEV_MPL115A2_H
#define GC_DEV_MPL115A2_H
void gc_dev_adafruit_MPL115A2_pressure_open(void);
uint32_t gc_dev_adafruit_MPL115A2_pressure_pa_read(void);
void gc_dev_adafruit_MPL115A2_pressure_pa_test(void);
#endif
