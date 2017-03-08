/*******************************
 *
 * File: gc_dev_honeywell_HIH6131_temperature.h
 *
 * Contains prototypes for humidty sensor functions
 *
 ******************************/

#include <Arduino.h>

//#define _PIN_GC_HIH6131_ AX

#ifndef GC_DEV_HIH6131_HUMIDITY_H
#define GC_DEV_HIH6131_HUMIDITY_H
void gc_dev_honeywell_HIH6131_humidity_open(void);
uint16_t gc_dev_honeywell_HIH6131_humidity_pct_read(void);
void gc_dev_honeywell_HIH6131_humidity_pct_test(void);
#endif
