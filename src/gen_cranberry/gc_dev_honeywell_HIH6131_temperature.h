/*******************************
 *
 * File: gc_dev_honeywell_HIH6131_temperature.h
 *
 * Contains prototypes for humidty sensor functions
 *
 ******************************/

#include <Arduino.h>

//#define _PIN_GC_HIH6131_ AX

#ifndef GC_DEV_HIH6131_TEMPERATURE_H
#define GC_DEV_HIH6131_TEMPERATURE_H
void gc_dev_honeywell_HIH6131_temperature_open(void);
uint16_t gc_dev_honeywell_HIH6131_temperature_centik_read(void);
void gc_dev_honeywell_HIH6131_temperature_centik_test(void);
#endif
