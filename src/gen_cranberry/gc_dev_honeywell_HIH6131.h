#include <Arduino.h>

//#define _PIN_GC_HIH6131_ AX

#ifndef GC_DEV_HIH6131_H
#define GC_DEV_HIH6131_H
void gc_dev_honeywell_HIH6131_open(void);
uint16_t gc_dev_honeywell_HIH6131_temp_centik_read(void);
uint16_t gc_dev_honeywell_HIH6131_humidity_pct_read(void);
#endif
